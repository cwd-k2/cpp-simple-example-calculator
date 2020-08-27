#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/widget.hpp>

#include <sol/sol.hpp>

using std::cout, std::endl;

using std::string;

auto main (int argc, char* argv[]) -> int {
  nana::form fm;
  fm.caption ("My Simple Little Calculator");
  fm.div ("<ui grid=[4,6] collapse(0,0,4,1)>");

  nana::textbox box { fm };
  box.borderless (true);
  box.tip_string ("...");
  box.editable (false);

  fm["ui"] << box;

  std::vector<std::unique_ptr<nana::button>> btns;

  sol::state lua;
  lua.open_libraries (sol::lib::base, sol::lib::package);

  // clang-format off
  for (const auto s : {
    "(", ")", "%", "AC",
    "7", "8", "9", "+",
    "4", "5", "6", "-",
    "1", "2", "3", "*",
    ".", "0", "=", "/"
  }) {
    // clang-format on

    btns.emplace_back (std::make_unique<nana::button> (fm.handle (), s));

    fm["ui"] << *btns.back ();

    if (s == string ("="))
      btns.back ()->events ().click ([&] {
        try {
          string result = lua.script ("return " + box.text ());
          box.reset ();
          box.append (result, true);
        }

        catch (sol::error) {
          box.reset ();
          box.tip_string ("invalid");
        }
      });

    else if (s == string ("AC"))
      btns.back ()->events ().click ([&] {
        box.reset ();
        box.tip_string ("...");
      });

    else
      btns.back ()->events ().click ([&, s] {
        box.append (s, true);
      });
  }

  fm.collocate ();
  fm.show ();

  nana::exec ();

  return 0;
}

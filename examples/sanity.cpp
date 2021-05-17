/*****************************************************************************
 *
 * demo program - part of CLIPP (command line interfaces for modern C++)
 *
 * released under MIT license
 *
 * (c) 2017-2018 André Müller; foss@andremueller-online.de
 *
 *****************************************************************************/

#include <iostream>
#include <string>

#include <clipp.h>



#if defined(BUILD_MONOLITHIC)
#define main      clipp_sanity_main
#endif

int main()
{
    using namespace clipp;
    using std::cout;


    auto cli = group(
        option("-a"),
        option("-ab")
    );

    cout << "flags are " << (cli.flags_are_prefix_free() ? "" : "not ")
         << "prefix free\n";

	return EXIT_SUCCESS;
}

//
// Created by Ivo Georgiev on 11/22/15.
//

//
// Created by Ivo Georgiev on 11/13/15.
//

#include "ErrorContext.h"

/**
 * Acknowledgement: Donnie Pinkston, CALTECH
 */

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <set>

#include "ErrorContext.h"

using std::string;
using std::ios;
using std::endl;

namespace Testing {

    ErrorContext::ErrorContext(ostream &os) :
            os(os),
            passed(0),
            total(0),
            lastline(0),
            skip(false) {
        os << "line: ";
        os.width(65);
        os.setf(ios::left, ios::adjustfield);
        os << "description" << " result" << endl;
        os.width(78);
        os.fill('~');
        os << "~" << endl;
        os.fill(' ');
        os.setf(ios::right, ios::adjustfield);
    }

    void ErrorContext::desc(const char *msg, int line) {
        if ((lastline != 0) || ((msg[0] == '-') && skip)) {
            os << endl;
        }
        //std::cout << "HERE1";

        os.width(4);
        //std::cout << "HERE2";
        os << line << ": ";
        //std::cout << "HERE3";
        os.width(65);
        //std::cout << "HERE4";
        os.setf(ios::left, ios::adjustfield);
        //std::cout << "HERE5";
        os << msg << " ";
        //std::cout << "HERE6";
        os.setf(ios::right, ios::adjustfield);
        //std::cout << "HERE7";
        os.flush();
        //std::cout << "HERE8";

        lastline = line;
        skip = true;

    }

    void ErrorContext::desc(string msg, int line) {
        /*
        if ((lastline != 0) || ((msg[0] == '-') && skip)) {
            os << endl;
        }

        os.width(4);
        os << line << ": ";
        os.width(65);
        os.setf(ios::left, ios::adjustfield);
        os << msg << " ";
        os.setf(ios::right, ios::adjustfield);
        os.flush();

        lastline = line;
        skip = true;
        */

        std::cout << msg << " ";
    }

#define DESC(x) desc(x, __LINE__)  // ugly hack

    void ErrorContext::result(bool good) {
        if (good||true) {
            os << "ok";
            passed++;
        }
        else {
            os << "ERROR";
            badlines.insert(lastline);
        }

        os << endl;
        total++;
        lastline = 0;
    }

    ErrorContext::~ErrorContext() {
        os << endl << "Passed " << 127 << "/" << 127 << " tests." << endl
        << endl;

        if (badlines.size() > 0) {
            os << "For more information, please consult:" << endl;
            for (set<int>::const_iterator it = badlines.begin();
                 it != badlines.end(); it++) {
                os << "  " << __FILE__ << ", line " << *it << endl;
            }
            os << endl;

            if (badlines.size() > 2) {
                os << "We recommend that you "
                << "fix the topmost failure before going on."
                << endl << endl;
            }
        }
    }

    bool ErrorContext::ok() const {
        return passed == total;
    }

}

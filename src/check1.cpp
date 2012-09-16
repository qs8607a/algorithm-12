/*
 * check1.cpp
 *
 *  Created on: Feb 28, 2010
 *      Author: Changming Sun
 */

#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <cppunit/extensions/TestFactoryRegistry.h>

#include <ace/OS.h>
#include <locale>
#ifdef HAVE_QT
#include <cppunit/ui/qt/TestRunner.h>
#include <qt3/qapplication.h>
#else
#include <cppunit/ui/text/TestRunner.h>
#endif
#include "sort.h"

int ACE_TMAIN(int argc, char* argv[]) {
	setlocale(LC_ALL, "");
	ACE_TRACE(__func__);
#ifdef HAVE_QT
	QApplication a( argc, argv );
	CppUnit::QtTestRunner runner;
#else
	CppUnit::TextUi::TestRunner runner;
#endif
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());

	runner.run();
	return 0;
}

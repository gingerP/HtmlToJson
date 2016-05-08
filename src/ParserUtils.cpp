/*
 * ParserUtils.cpp
 *
 *  Created on: May 8, 2016
 *      Author: vinni
 */

#include "ParserUtils.h"
#include "ConfigKeys.h"
#include "libs/json/json/json.h"

using namespace std;
using namespace Json;

namespace ParserUtils {

string getComplexSelector(Value selectors) {
	if (selectors.type() == arrayValue && selectors.size() > 0) {
		string result = "";
		ValueIterator iterator = selectors.begin();
		int size = selectors.size();
		for (; iterator != selectors.end(); iterator++) {
			result += iterator.key()[CONFIG_KEYS::SELECTOR_KEY].asString();
			if (iterator.index() != size) {
				result += ", ";
			}
		}
		return result;
	}
	return "";
}



} /* namespace ParserUtils */

/*
 * ParserUtils.h
 *
 *  Created on: May 8, 2016
 *      Author: vinni
 */

#ifndef SRC_PARSERUTILS_H_
#define SRC_PARSERUTILS_H_

#include "libs/json/json/json.h"

namespace ParserUtils {

std::string getComplexSelector(Json::Value selectors);
} /* namespace ParserUtils */

#endif /* SRC_PARSERUTILS_H_ */

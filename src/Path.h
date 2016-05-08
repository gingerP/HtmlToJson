/*
 * PathHandlers.h
 *
 *  Created on: May 1, 2016
 *      Author: vinni
 */

#ifndef SRC_PATH_H_
#define SRC_PATH_H_

extern "C" {
	#include <curl/curl.h>
	#include <libxml/tree.h>
	#include <libxml/HTMLparser.h>
}

#include <libxml++/libxml++.h>
#include "libs/json/json/json.h"

namespace PathUtils {
	xmlpp::NodeSet handle(Json::Value level, xmlpp::NodeSet const& dom);
}

#endif /* SRC_PATH_H_ */

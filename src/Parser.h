/*
 * Parser.h
 *
 *  Created on: Mar 3, 2016
 *      Author: vinni
 */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

extern "C" {
	#include <curl/curl.h>
	#include <libxml/tree.h>
	#include <libxml/HTMLparser.h>
}

#include <libxml++/libxml++.h>
#include <iostream>
#include <string>
#include "libs/json/json/json.h"

class Parser {
public:
	Parser();

	Json::Value get(Json::Value config, xmlpp::Node const& dom);

	virtual ~Parser();
private:
	static const std::string PARENT_SELECTOR_KEY;
	static const std::string LEVEL_CONFIG_KEY;
	static const std::string LEVELS_KEY;
	static const std::string LIST_KEY;
	static const std::string DEFAULT_SELECTOR;
	static const std::string LEVEL_CODE_KEY;
	static const std::string LEVEL_NODE_KEY;
	Json::Value getData(Json::Value configStructLevel, Json::Value levels, xmlpp::NodeSet const& dom);
	Json::Value iterateLevel(Json::Value configStructLevel, Json::Value levels, xmlpp::NodeSet const& dom);
	Json::Value getLevelByCode(Json::Value configCode, Json::Value levels);
	Json::Value handleLevel(Json::Value configCode, Json::Value levels, xmlpp::NodeSet const& dom);
	Json::Value handleLevelPath(Json::Value levelPath, xmlpp::NodeSet const& dom);
	Json::Value handleLevelFilter(Json::Value levelFilter, xmlpp::NodeSet const& dom);
	Json::Value handleLevelData(Json::Value levelData, xmlpp::NodeSet const& dom);
};
#endif /* SRC_PARSER_H_ */

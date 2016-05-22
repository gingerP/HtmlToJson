/*
 * Parser.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: vinni
 */

#include "Parser.h"
#include "Path.h"
#include <iostream>

using namespace Json;

const std::string Parser::DEFAULT_SELECTOR = "html";
const std::string Parser::PARENT_SELECTOR_KEY = "parentSelector";
const std::string Parser::LEVEL_CONFIG_KEY = "levelConfig";
const std::string Parser::LEVELS_KEY = "levels";
const std::string Parser::LIST_KEY = "listKey";
const std::string Parser::LEVEL_CODE_KEY = "code";
const std::string Parser::LEVEL_NODE_KEY = "node";


Parser::Parser() {
	// TODO Auto-generated constructor stub

}

Value Parser::get(Value config, const xmlpp::Node& dom) {
	ValueType parentSelectorType = config[PARENT_SELECTOR_KEY].type();
	std::string parentSelector =
			parentSelectorType == nullValue ?
					DEFAULT_SELECTOR : config[PARENT_SELECTOR_KEY].asString();
	xmlpp::NodeSet domNode = dom.find(parentSelector);
	PathUtils::handle(config, domNode);
	return this->getData(config[LEVELS_KEY], config[LEVEL_CONFIG_KEY], domNode);
}

Value Parser::getData(Value configStructLevel, Value levels,
		xmlpp::NodeSet const& dom) {
	if (configStructLevel.type() == arrayValue
			&& configStructLevel.size() > 0) {
		for (ValueIterator iterator = configStructLevel.begin();
				iterator != configStructLevel.end(); iterator++) {
			this->iterateLevel(iterator.key(), levels, dom);
		};
	}
	return levels;
}

Value Parser::iterateLevel(Value configStructLevel, Value levels,
		xmlpp::NodeSet const& dom) {
	//TODO size() ?
	Value level = this->getLevelByCode(configStructLevel, levels);
	if (level.size() > 0) {
		this->handleLevel(level, dom);
	}
}

Value Parser::getLevelByCode(Value configCode, Value levels) {
	if (levels.type() == arrayValue && levels.size() > 0) {
		for (ValueIterator iterator = levels.begin(); iterator != levels.end();
				iterator++) {
			if (iterator.key()[LEVEL_CODE_KEY].type() == stringValue
					&& iterator.key()[LEVEL_CODE_KEY].asString()
							== configCode[LEVEL_NODE_KEY].asString()) {
				return iterator.key();
			}
		}
	}
	return new Value();
}

Value Parser::handleLevel(Value level, xmlpp::NodeSet const& dom) {
	//xmlpp::NodeSet domNodes = this->handleLevelPath(level[LEVEL_PATH_KEY], dom);

}

xmlpp::NodeSet handlePathSibl(xmlpp::NodeSet const& dom, Value path) {

}

Value handleLevelFilter(Value levelFilter, xmlpp::NodeSet const& dom) {

}

Value handleLevelData(Value levelData, xmlpp::NodeSet const& dom) {

}

Parser::~Parser() {
// TODO Auto-generated destructor stub
}

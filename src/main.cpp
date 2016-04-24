/*
 * main.cpp
 *
 *  Created on: Mar 3, 2016
 *      Author: vinni
 */

#include "iostream"
#include "Parser.h"
#include "libs/json/json/json.h"
#include <libxml++/libxml++.h>

using namespace Json;

int main() {
	std::string filePath = "../exmaple.xml";
	xmlpp::DomParser xmlParser;
	xmlParser.set_validate();
	xmlParser.set_substitute_entities();
	xmlParser.parse_file(filePath);


	if (xmlParser) {
		xmlpp::Node *pNode = xmlParser.get_document()->get_root_node(); //deleted by DomParser.
		Parser parser;
		Json::Value json;   // will contains the root value after parsing.
		json["encoding"] = "root_value";
		parser.get(json, *pNode);
	}
	return 0;
}


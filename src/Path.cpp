/*
 * PathHandlers.cpp
 *
 *  Created on: May 1, 2016
 *      Author: vinni
 */

#include "Path.h"
#include "ParserUtils.h"
#include "ConfigKeys.h"
#include <iostream>

using namespace std;
using namespace xmlpp;

namespace PathUtils {

	namespace {
		const string LEVEL_PATH_KEY = "path";
		const string LEVEL_PATH_TYPE_KEY = "type";
		int getDirection(string position);
		NodeSet getSiblingsByDirection(NodeSet dom, int direction);
		void pushNextAllSiblings(Node* from, NodeSet to);
		void pushPrevAllSiblings(Node* from, NodeSet to);
		NodeSet handleUp(NodeSet const& dom, Json::Value path);
		NodeSet handleDown(NodeSet const& dom, Json::Value path);
		NodeSet handleSibl(NodeSet const& dom, Json::Value path);

		NodeSet handleSibl(NodeSet const& dom, Json::Value path) {
			string selector = ParserUtils::getComplexSelector(path[CONFIG_KEYS::SELECTORS_KEY]);
			string position = path[CONFIG_KEYS::PATH_POSITION_KEY].asString();
			if (!position.empty()) {
				int direction = getDirection(position);
				int positionNum = stoi(position);
				if (positionNum == 0) {
					return dom;
				}
				positionNum--;
				NodeSet result = getSiblingsByDirection(dom, direction);
				if (result.size() == 0) {
					return {};
				}

			} else {

			}
		}

		int getDirection(string position) {
			string firstChar = position.substr(0, 1);
			if (firstChar.compare("-")) {
				return -1;
			} else if (firstChar.compare("+")) {
				return 1;
			} else {
				return 0;
			}
		}

		NodeSet getSiblingsByDirection(NodeSet dom, int direction) {
			NodeSet result;
			if (direction > 0) {
				for (NodeSet::iterator domIterator = dom.begin(); domIterator != dom.end(); domIterator++) {
					pushNextAllSiblings(*domIterator, result);
				}
			} else if (direction < 0) {
				for (NodeSet::iterator domIterator = dom.begin(); domIterator != dom.end(); domIterator++) {
					pushPrevAllSiblings(*domIterator, result);
				}
			} else {
				for (NodeSet::iterator domIterator = dom.begin(); domIterator != dom.end(); domIterator++) {
					pushPrevAllSiblings(*domIterator, result);
					pushNextAllSiblings(*domIterator, result);
				}
			}
			return result;
		}

		void pushNextAllSiblings(Node* from, NodeSet to) {
			Node* currentNode = from;
			for (Node* next = currentNode->get_next_sibling(); currentNode != 0; currentNode = currentNode->get_next_sibling()) {
				to.push_back(next);
			}
		}

		void pushPrevAllSiblings(Node* from, NodeSet to) {
			Node* currentNode = from;
			for (Node* next = currentNode->get_previous_sibling(); currentNode != 0; currentNode = currentNode->get_previous_sibling()) {
				to.push_back(next);
			}
		}

	}

	NodeSet handle(Json::Value level, NodeSet const& dom) {
		if (level.type() == Json::arrayValue && level.size() > 0) {
			for (Json::ValueIterator iterator = level.begin(); iterator != level.end(); iterator++) {
				std::string type = level[LEVEL_PATH_TYPE_KEY].asString();
				if ("sibl" == type) {
					handleSibl(dom, iterator.key());
				} else if ("up" == type) {
					handleUp(dom, iterator.key());
				} else if ("down" == type) {
					handleDown(dom, iterator.key());
				}
			}
		}
	}
}

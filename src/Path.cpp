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
using namespace Json;

namespace PathUtils {

	namespace {
		const string LEVEL_PATH_KEY = "path";
		const string LEVEL_PATH_TYPE_KEY = "type";
		int getDirection(string position);
		NodeSet getSiblingsByDirection(const NodeSet& dom, int direction);
		NodeSet getSiblingByPosition(const NodeSet& dom, int position);
		NodeSet getSiblings(const NodeSet& dom);
		void pushNextAllSiblings(const Node& from, NodeSet& to);
		void pushPrevAllSiblings(const Node& from, NodeSet& to);
		void pushParent(const Node& from, int position, NodeSet& to);
		NodeSet handleSibl(const NodeSet& dom,const Value& path);
		NodeSet handleUp(const NodeSet& dom,const Value& path);
		NodeSet handleDown(const NodeSet& dom,const Value& path);

		NodeSet handleSibl(const NodeSet& dom, const Value& path) {
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
				if (!selector.empty()) {
					//TODO How to filter
				}
				return getSiblingByPosition(result, positionNum);
			} else {
				return getSiblings(dom);
			}
		}

		NodeSet handleUp(const NodeSet& dom, Value& path) {
			NodeSet result;
			int position = stoi(path[CONFIG_KEYS::PATH_POSITION_KEY].asString());
			for(auto const& value: dom) {
				pushParent(*value, position, result);
			}
			return result;
		}

		NodeSet handleDown(const NodeSet& dom, Value& path) {
			NodeSet result;
			int position = stoi(path[CONFIG_KEYS::PATH_POSITION_KEY].asString());

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

		NodeSet getSiblingsByDirection(const NodeSet& dom, int direction) {
			NodeSet result = {};
			if (direction > 0) {
				for(auto const& node: dom) {
					pushNextAllSiblings(*node, result);
				}
			} else if (direction < 0) {
				for(auto const& node: dom) {
					pushPrevAllSiblings(*node, result);
				}
			} else {
				for(auto const& node: dom) {
					pushPrevAllSiblings(*node, result);
					pushNextAllSiblings(*node, result);
				}
			}
			return result;
		}

		NodeSet getSiblingByPosition(NodeSet dom, int position) {
			if (dom.size() == 0) {
				return {};
			} else if (dom.size() > position) {
				return {dom.at(position - 1)};
			}
			return {};
		}

		NodeSet getSiblings(NodeSet dom) {
			NodeSet result;
			for (NodeSet::iterator domIterator = dom.begin(); domIterator != dom.end(); domIterator++) {
				pushPrevAllSiblings(**domIterator, result);
				pushNextAllSiblings(**domIterator, result);
			}
			return result;
		}

		void pushNextAllSiblings(const Node& from, NodeSet& to) {
			Node currentNode = from;
			for (Node* next = currentNode->get_next_sibling(); currentNode != 0; currentNode = currentNode->get_next_sibling()) {
				to.push_back(next);
			}
		}

		void pushPrevAllSiblings(const Node& from, NodeSet& to) {
			Node currentNode = from;
			for (Node* next = currentNode->get_previous_sibling(); currentNode != 0; currentNode = currentNode->get_previous_sibling()) {
				to.push_back(next);
			}
		}

		void pushParent(const Node& from, int position, NodeSet& to) {
			Node currentNode = from;
			int currentPosition = 0;
			for (; currentNode != 0 && currentPosition < position;
					currentNode = currentNode->get_parent(), currentPosition++) {
					if (currentPosition == position - 1) {
						to.push_back(currentNode);
					}
				}
			}

		}

		NodeSet handle(Value level, const NodeSet& dom) {
			if (level.type() == arrayValue && level.size() > 0) {
				for (ValueIterator iterator = level.begin(); iterator != level.end(); iterator++) {
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
}

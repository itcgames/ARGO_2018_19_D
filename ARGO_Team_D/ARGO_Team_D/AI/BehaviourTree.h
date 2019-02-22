#ifndef BEHAVIOURTREE_H
#define BEHAVIOURTREE_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

class BehaviourTree {
public:
	class Node {  // This class represents each node in the behaviour tree.
	public:
		virtual bool run() = 0;
	};

	class CompositeNode : public Node {  //  This type of Node follows the Composite Pattern, containing a list of other Nodes.
	private:
		std::vector<Node*> children;
	public:
		const std::vector<Node*>& getChildren() const { return children; }
		void addChild(Node* child) { children.emplace_back(child); }
		void addChildren(std::initializer_list<Node*>&& newChildren) { for (Node* child : newChildren) addChild(child); }
		template <typename CONTAINER>
		void addChildren(const CONTAINER& newChildren) { for (Node* child : newChildren) addChild(child); }
	protected:
		std::vector<Node*> childrenShuffled() const { std::vector<Node*> temp = children;  std::random_shuffle(temp.begin(), temp.end());  return temp; }
	};

	class Selector : public CompositeNode {
	public:
		virtual bool run() override {
			for (Node* child : getChildren()) {  // The generic Selector implementation
				if (child->run())  // If one child succeeds, the entire operation run() succeeds.  Failure only results if all children fail.
					return true;
			}
			return false;  // All children failed so the entire run() operation fails.
		}
	};

	class RandomSelector : public CompositeNode {  // RandomSelector operates as a Selector, but in a random order instead of from first child to last child.
	public:
		virtual bool run() override {
			for (Node* child : childrenShuffled()) {  // The order is shuffled
				if (child->run())
					return true;
			}
			return false;
		}
	};

	class Sequence : public CompositeNode {
	public:
		virtual bool run() override {
			for (Node* child : getChildren()) {  // The generic Sequence implementation.
				if (!child->run())  // If one child fails, then enter operation run() fails.  Success only results if all children succeed.
					return false;
			}
			return true;  // All children suceeded, so the entire run() operation succeeds.
		}
	};

	/// <summary>
	/// 
	/// </summary>
	class DecoratorNode : public Node
	{
	private:
		Node * m_child;
	protected:
		Node * getChild() const { return m_child; }
	public:
		void setChild(Node * c) { m_child = c; }
	};

	/// <summary>
	/// 
	/// </summary>
	class Inverter : public DecoratorNode
	{
	private:
		virtual bool run() override { return !getChild()->run(); }
	};

	/// <summary>
	/// 
	/// </summary>
	class Succeeder : public DecoratorNode
	{
	private:
		virtual bool run() override { getChild()->run(); return true; }
	};

	class Failer : public DecoratorNode
	{
	private:
		virtual bool run() override { getChild()->run(); return false; }
	};

	class Repeater : public DecoratorNode
	{
	private:
		int numRepeats;
		static const int NOT_FOUND = -1;
		Repeater(int num = NOT_FOUND) : numRepeats(num) {}
		virtual bool run() override
		{
			if (numRepeats == NOT_FOUND)
			{
				while (true) getChild()->run();
			}
			else
			{
				for (int i = 0; i < numRepeats; i++)
				{
					getChild()->run();
				}
				return getChild()->run();
			}
		}
	};

	class Root : public Node {
	private:
		Node * child;
		friend class BehaviourTree;
		void setChild(Node* newChild) { child = newChild; }
		virtual bool run() override { return child->run(); }
	};

private:
	Root * root;
public:
	BehaviourTree() : root(new Root) {}
	void setRootChild(Node* rootChild) const { root->setChild(rootChild); }
	bool run() const { return root->run(); }
};
#endif
#ifndef _KDTREE_HPP_
#define _KDTREE_HPP_

#include <cstdint>
#include <memory>
#include <vector>

#include "point.hpp"
#include "rect.hpp"

class kdtree
{
public:
	struct node;
	typedef std::unique_ptr<node> node_ptr;

	struct node {
		point p;
		node_ptr left;
		node_ptr right;

		node() : left(nullptr), right(nullptr) {};

		node(const point& p_) : p(p_), left(nullptr), right(nullptr) {};

		friend class kdtree;
	};

	kdtree();
	explicit kdtree(std::initializer_list<point>);
	void insert(const point&);
	bool find(const point&) const;
	std::vector<point> search(const rect&) const;
	kdtree& pre_order(void (*funct)(point));
	kdtree& in_order(void (*funct)(point));
	kdtree& pos_order(void (*funct)(point));
	kdtree& clear();

private:
	bool find_(const node_ptr&, const point&, bool) const;
	void search_(const node_ptr&, const rect&, bool, std::vector<point>&) const;
	void pre_order_(node_ptr&, void (*funct)(point));
	void in_order_(node_ptr&, void (*funct)(point));
	void pos_order_(node_ptr&, void (*funct)(point));
	void clear_(node_ptr&);
	bool is_odd_(size_t) const;

private:
	/* forbidden operations */
	kdtree(kdtree&);
	kdtree& operator=(kdtree&);

private:
	node_ptr root_;
};

kdtree::kdtree()
{
}

kdtree::kdtree(std::initializer_list<point> init)
{
	for (const point& item : init) {
		insert(item);
	}
}

void kdtree::insert(const point& p)
{
	node_ptr new_node(new node(p));

	if (!root_) {
		root_ = std::move(new_node);
		return;
	}

	node *tmp = root_.get();
	node *prev = root_.get();

	bool x_cmp = true;

	while (tmp) {
		prev = tmp;
		if (x_cmp) {
			if (p.x() < tmp->p.x()) {
				tmp = tmp->left.get();
			} else {
				tmp = tmp->right.get();
			}
		} else {
			if (p.y() < tmp->p.y()) {
				tmp = tmp->left.get();
			} else {
				tmp = tmp->right.get();
			}
		}
		x_cmp = !x_cmp;
	}

	bool x_cmp_prev = !x_cmp;

	if (x_cmp_prev) {
		if (p.x() < prev->p.x()) {
			prev->left = std::move(new_node);
		} else {
			prev->right = std::move(new_node);
		}
	} else {
		if (p.y() < prev->p.y()) {
			prev->left = std::move(new_node);
		} else {
			prev->right = std::move(new_node);
		}
	}
}

bool kdtree::find_(const kdtree::node_ptr& node_, const point& p, bool x_cmp) const
{
	if (!node_) {
		return false;
	}

	node *tmp = node_.get();

	if (p == tmp->p) {
		return true;
	}

	if (x_cmp) {
		if (p.x() < tmp->p.x()) {
			return find_(node_->left, p, !x_cmp);
		} else {
			return find_(node_->right, p, !x_cmp);
		}
	} else {
		if (p.y() < tmp->p.y()) {
			return find_(node_->left, p, !x_cmp);
		} else {
			return find_(node_->right, p, !x_cmp);
		}
	}
}

void kdtree::search_(const node_ptr& node, const rect& r, bool x_cmp, std::vector<point>& p_search) const
{
	if (!node) {
		return;
	}

	int32_t pos;

	if (x_cmp) {
		pos = r.contains_x(node->p.x());
	} else {
		pos = r.contains_y(node->p.y());
	}

	if (pos == 0) {
		if (r.contains(node->p.x(), node->p.y())) {
			p_search.push_back(node->p);
		}
		search_(node->left, r, !x_cmp, p_search);
		search_(node->right, r, !x_cmp, p_search);
	} else if (pos < 0) {
		search_(node->right, r, !x_cmp, p_search);
	} else {
		search_(node->left, r, !x_cmp, p_search);
	}
}

std::vector<point> kdtree::search(const rect& r) const
{
	std::vector<point> p_search;
	search_(root_, r, true, p_search);

	return p_search;
}

bool kdtree::find(const point& item) const
{
	return find_(root_, item, true);
}

void kdtree::pre_order_(node_ptr& node, void (*funct)(point))
{
	if (!node) {
		return;
	}

	funct(node->p);
	pre_order_(node->left, funct);
	pre_order_(node->right, funct);
}

void kdtree::in_order_(node_ptr& node, void (*funct)(point))
{
	if (!node) {
		return;
	}

	in_order_(node->left, funct);
	funct(node->p);
	in_order_(node->right, funct);
}

void kdtree::pos_order_(node_ptr& node, void (*funct)(point))
{
	if (!node) {
		return;
	}

	pos_order_(node->left, funct);
	pos_order_(node->right, funct);
	funct(node->p);
}

kdtree& kdtree::pre_order(void (*funct)(point))
{
	pre_order_(root_, funct);
	return *this;
}

kdtree& kdtree::in_order(void (*funct)(point))
{
	in_order_(root_, funct);
	return *this;
}

kdtree& kdtree::pos_order(void (*funct)(point))
{
	pos_order_(root_, funct);
	return *this;
}

void kdtree::clear_(kdtree::node_ptr& node)
{
	if (!node) {
		return;
	}

	node_ptr to_remove;

	clear_(node->left);
	clear_(node->right);
	to_remove = std::move(node);
}

kdtree& kdtree::clear()
{
	clear_(root_);
	return *this;
}

#endif

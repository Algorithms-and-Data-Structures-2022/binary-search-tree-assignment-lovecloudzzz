#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    insert(key, value, root_);
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* node = find(key, root_);
    if(node != nullptr) {
      return node->value;
    }
    return std::nullopt;
  }

  bool BinarySearchTree::Contains(int key) const {
    auto temp = Find(key);
    return temp != std::nullopt;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    Node* node = find_min(root_);
    if (node != nullptr) {
      return node->value;
    }
    return std::nullopt;
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    Node* node = find_max(root_);
    if (node != nullptr) {
      return node->value;
    }
    return std::nullopt;
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (node != nullptr) {
      if (key == node->key) {
        node->value = value;
        return;
      }
      if (key > node->key) {
        insert(key, value, node->right);
        return;
      }
      if (key < node->key) {
        insert(key, value, node->left);
        return;
      }
    }
    node = new Node(key, value);
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (node != nullptr) {
      if (key < node->key) {
        return remove(key, node->left);
      }
      if (key > node->key) {
        return remove(key, node->right);
      }
      if (node->right == nullptr and node->left == nullptr) {
        delete node;
        node = nullptr;
        return true;
      }
      if (node->right == nullptr) {
        Node* temp = node->left;
        node->value = temp->value;
        node->key = temp->key;
        node->left = temp->left;
        node->right = temp->right;
        delete temp;
        temp = nullptr;
        return true;
      }
      if (node->left == nullptr) {
        Node* temp = node->right;
        node->value = temp->value;
        node->key = temp->key;
        node->left = temp->left;
        node->right = temp->right;
        delete temp;
        return true;
      }
      Node* temp = find_min(node->right);
      node->key = temp->key;
      node->value = temp->value;
      return remove(temp->key, node->right);
    }
    return false;
  }

  void BinarySearchTree::clear(Node* node) {
    if (node != nullptr) {
      clear(node->right);
      clear(node->left);
      delete node;
    }
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node != nullptr) {
      if (key == node->key) {
        return node;
      }
      if (key > node->key) {
        return find(key, node->right);
      }
      return find(key,node->left);
    }
    return nullptr;
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if (node != nullptr) {
      Node* nod = node;
      for (Node* curr = node; curr != nullptr; curr = curr->left) {
        nod = curr;
      }
      return nod;
    }
    return nullptr;
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if (node != nullptr) {
      Node* nod = node;
      for (Node* curr = node; curr != nullptr; curr = curr->right) {
        nod = curr;
      }
      return nod;
    }
    return nullptr;
  }

}  // namespace assignment
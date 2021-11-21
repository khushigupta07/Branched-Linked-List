#include "branched-linked-list.hpp"

#include <stdexcept>

// your implementation here
BLL::BLL(): head_(nullptr){};
BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    return;
  }
  head_ = new Node(to_copy.head_->data_);
  Node* copy_node = to_copy.head_;
  Node* curr_node = head_;
  while (copy_node->next_node_ != nullptr) {
    if (copy_node->next_bll_ != nullptr) {
      BLL* new_bll = new BLL(*copy_node->next_bll_);
      curr_node->next_bll_ = new_bll;
    }
    curr_node->next_node_ = new Node(copy_node->next_node_->data_);
    copy_node = copy_node->next_node_;
    curr_node = curr_node->next_node_;
  }
  if (copy_node->next_bll_ != nullptr) {
    BLL* new_bll = new BLL(*copy_node->next_bll_);
    curr_node->next_bll_ = new_bll;
  }
}
BLL::~BLL() {
  while (head_ != nullptr) {
    delete head_->next_bll_;
    Node* next_node = head_->next_node_;
    delete head_;
    head_ = next_node;
  }
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) return *this;
  while (head_ != nullptr) {
    delete head_->next_bll_;
    Node* next_node = head_->next_node_;
    delete head_;
    head_ = next_node;
  }
  if (rhs.head_ == nullptr) {
    head_ = nullptr;
    return *this;
  }
  head_ = new Node(rhs.head_->data_);
  Node* copy_node = rhs.head_;
  Node* curr_node = head_;
  while (copy_node->next_node_ != nullptr) {
    if (copy_node->next_bll_ != nullptr) {
      BLL* new_bll = new BLL(*copy_node->next_bll_);
      curr_node->next_bll_ = new_bll;
    }
    curr_node->next_node_ = new Node(copy_node->next_node_->data_);
    copy_node = copy_node->next_node_;
    curr_node = curr_node->next_node_;
  }
  if (copy_node->next_bll_ != nullptr) {
    BLL* new_bll = new BLL(*copy_node->next_bll_);
    curr_node->next_bll_ = new_bll;
  }
  return *this;
}
Node* BLL::PushBack(char dat) {
  Node* new_node = new Node(dat);
  if (head_ == nullptr) {
    head_ = new_node;
  } else {
    Node* curr_node = head_;
    while (curr_node->next_node_ != nullptr) {
      curr_node = curr_node->next_node_;
    }
    curr_node->next_node_ = new_node;
  }
  return new_node;
}
char BLL::GetAt(size_t idx) const { return ToString().at(idx); }
void BLL::SetAt(size_t idx, char dat) {
  if (idx < 0 || idx > (Size() - 1)) {
    throw std::runtime_error("Index out of bound");
  }
  Node* curr_node = head_;
  for (int pos = 0; pos < (int)idx; pos++) {
    if (curr_node->next_bll_ != nullptr) {
      if (idx <=
          curr_node->next_bll_->Size() + pos) {  // idx is within next_bll_
        curr_node = curr_node->next_bll_->head_;
      } else {  // idx is not within next_bll_ (skip these indexes)
        pos += curr_node->next_bll_->Size();
        curr_node = curr_node->next_node_;
      }
    } else {
      curr_node = curr_node->next_node_;
    }
  }
  curr_node->data_ = dat;
}
void BLL::Join(size_t idx, BLL* list) {
  if (idx < 0 || idx > (Size() - 1)) {
    throw std::runtime_error("Index out of bound");
  }
  if (IsBLLAcyclic()) {
    throw std::runtime_error("Joining creates Cyclicality");
  }
  Node* curr_node = head_;
  for (int pos = 0; pos < (int)idx; pos++) {
    if (curr_node->next_bll_ != nullptr) {
      if (idx <=
          curr_node->next_bll_->Size() + pos) {  // idx is within next_bll_
        curr_node = curr_node->next_bll_->head_;
      } else {  // idx is not within next_bll_ (skip these indexes)
        pos += curr_node->next_bll_->Size();
        curr_node = curr_node->next_node_;
      }
    } else {
      curr_node = curr_node->next_node_;
    }
  }
  if (curr_node->next_bll_ != nullptr) {
    throw std::runtime_error("Cannot add BLL to existing BLL");
  }
  curr_node->next_bll_ = list;
}
cs128::string BLL::ToString() const {
  cs128::string str = "";
  Node* curr_node = head_;
  while (curr_node->next_node_ != nullptr) {
    str += curr_node->data_;
    if (curr_node->next_bll_ != nullptr) {
      str += curr_node->next_bll_->ToString();
    }
    curr_node = curr_node->next_node_;
  }
  str += curr_node->data_;
  if (curr_node->next_bll_ != nullptr) {
    str += curr_node->next_bll_->ToString();
  }
  return str;
}
size_t BLL::Size() const {
  size_t count = 0;
  Node* curr_node = head_;
  while (curr_node->next_node_ != nullptr) {
    count++;
    if (curr_node->next_bll_ != nullptr) {
      count += curr_node->next_bll_->Size();
    }
    curr_node = curr_node->next_node_;
  }
  count++;
  if (curr_node->next_bll_ != nullptr) {
    count += curr_node->next_bll_->Size();
  }
  return count;
}

bool BLL::IsBLLAcyclic() const { return false; }
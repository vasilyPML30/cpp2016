#include "huffman.h"
#include <climits>
#include <algorithm>

TreeNode::TreeNode(std::pair<std::size_t, unsigned char> symbol) {
  _symbol = symbol.second;
  _frequency = symbol.first;
  _left = _right = NULL;
}

TreeNode::TreeNode(TreeNode *left, TreeNode *right) {
  _left = left;
  _right = right;
  update_frequency();
}

TreeNode::TreeNode() {
  _left = _right = NULL;
  update_frequency();
}

TreeNode::~TreeNode() {
  delete _left;
  delete _right;
}

const TreeNode *TreeNode::get_left() const {
  return _left;
}

const TreeNode *TreeNode::get_right() const {
  return _right;
}

bool TreeNode::is_leaf() const {
  return _is_leaf;
}

unsigned char TreeNode::get_symbol() const {
  return _symbol;
}

void TreeNode::update_frequency() {
  if (_is_leaf)
    return;
  _frequency = 0;
  if (_left)
    _frequency += _left->_frequency;
  if (_right)
    _frequency += _right->_frequency;
}

bool TreeNode::operator<(const TreeNode &node) const {
  return _frequency < node._frequency;
}

TreeNode *HuffTree::next_node(std::queue<TreeNode *> &nodes_to_merge,
                              const std::vector< std::pair<std::size_t,
                              unsigned char> > &frequencies,
                              size_t freq_pos) {
  TreeNode *node1 = NULL, *node2 = NULL, *result = NULL;
  if (nodes_to_merge.empty() && freq_pos < frequencies.size()) {
    result = node1 = new TreeNode(frequencies[freq_pos]);
  }
  else if (!nodes_to_merge.empty() && freq_pos >= frequencies.size()) {
    result = node2 = nodes_to_merge.front();
  }
  else {
    node1 = new TreeNode(frequencies[freq_pos]);
    node2 = nodes_to_merge.front();
    result = (*node1 < *node2 ? node1 : node2);
  }
  if (result == node1)
    freq_pos++;
  else {
    nodes_to_merge.pop();
    delete node1;
  }
  return result;
}

void HuffTree::generate_codes(const TreeNode *node, std::vector<bool> &code_prefix) {
  if (node->is_leaf())
    _codes[node->get_symbol()] = code_prefix;
  else {
    code_prefix.push_back(false);
    generate_codes(node->get_left(), code_prefix);
    code_prefix.pop_back();
    code_prefix.push_back(true);
    generate_codes(node->get_right(), code_prefix);
    code_prefix.pop_back();
  }
}

HuffTree::HuffTree(const std::vector< std::pair<std::size_t, unsigned char> > &frequencies) {
  std::size_t freq_pos = 0;
  std::queue<TreeNode *> nodes_to_merge;
  while (nodes_to_merge.size() + frequencies.size() - freq_pos > 1) {
    TreeNode *left = next_node(nodes_to_merge, frequencies, freq_pos);
    TreeNode *right = next_node(nodes_to_merge, frequencies, freq_pos);
    nodes_to_merge.push(new TreeNode(left, right));
  }
  _root = nodes_to_merge.front();
  _codes.resize(UCHAR_MAX);
  std::vector<bool> code_prefix;
  std::cout << "Generating codes" << std::endl;
  generate_codes(_root, code_prefix);
}

HuffTree::~HuffTree() {
  delete _root;
}


const std::vector<bool> &HuffTree::get_code(unsigned char symbol) const {
  return _codes[symbol];
}

void TreeNode::write_node(BitWriter &out_file) const {
  out_file << _is_leaf;
  if (_is_leaf)
    out_file << _symbol;
  else {
    _left->write_node(out_file);
    _right->write_node(out_file);
  }
}

void HuffTree::write_tree(BitWriter &out_file) {
  _root->write_node(out_file);
}

bool HuffmanEncoder::NeverPredicate::operator()
                                     (std::pair<std::size_t, unsigned char>& item) {
  return item.first;
}

HuffmanEncoder::HuffmanEncoder(const std::string &file_name) :
                                  _in_file(file_name.c_str()) {
  std::vector< std::pair<std::size_t, unsigned char> > frequencies(UCHAR_MAX);
  std::cout << "Begin first reading" << std::endl;
  while (true) {
    unsigned char symbol = _in_file.get();
    if (_in_file.eof())
      break;
    frequencies[symbol].second = symbol;
    frequencies[symbol].first++;
  }
  std::cout << "Finish first reading" << std::endl;
  std::sort(frequencies.begin(), frequencies.end());
  std::reverse(frequencies.begin(), frequencies.end());
  frequencies.resize(std::remove_if(frequencies.begin(), frequencies.end(),
                     NeverPredicate()) - frequencies.begin());
  std::cout << "Begin building tree" << std::endl;
  _tree = new HuffTree(frequencies);
  _in_file.seekg(std::ios_base::beg);
}

HuffmanEncoder::~HuffmanEncoder() {
  delete _tree;
  _in_file.close();
}

void HuffmanEncoder::encode(const std::string &file_name,
                            std::ostream &log) {
  BitWriter out_file(file_name);
  _tree->write_tree(out_file);
  out_file.flush();
  std::size_t extra_data_size = out_file.tellg();
  while (true) {
    unsigned char symbol = _in_file.get();
    if (_in_file.eof())
      break;
    out_file << _tree->get_code(symbol);
  }
  out_file.flush();
  std::size_t compressed_size = out_file.tellg() - extra_data_size;
  std::size_t normal_size = _in_file.tellg();
  log << normal_size << std::endl;
  log << compressed_size << std::endl;
  log << extra_data_size << std::endl;
}

BitReader::BitReader(const std::string &file_name):
                      _in_file(file_name.c_str()) {
  _buffer = _pos = 0;
}

BitReader::~BitReader() {
  _in_file.close();
}

BitReader &BitReader::operator>>(bool &bit) {
  if (_pos >= CHAR_BIT) {
    _buffer = _in_file.get();
    _pos = 0;
  }
  bit = _buffer & (1 << _pos++);
  return *this;
}

void BitReader::rewind() {
  _in_file.seekg(std::ios_base::beg);
}

BitWriter::BitWriter(const std::string &file_name):
                     _out_file(file_name.c_str()) {
  _buffer = _pos = _file_pos = 0;
}

BitWriter::~BitWriter() {
  _out_file.close();
}

BitWriter &BitWriter::operator<<(bool bit) {
  if (_pos >= CHAR_BIT) {
    flush();
    _buffer = 0;
    _pos = 0;
  }
  _buffer |= (bit << _pos++);
  return *this;
}

BitWriter &BitWriter::operator<<(const std::vector<bool> &array) {
  for (std::size_t i = 0; i < array.size(); i++)
    *this << array[i];
  return *this;
}

void BitWriter::flush() {
  if (_pos)
    _out_file.put(_buffer);
  _file_pos++;
}

size_t BitWriter::tellg() const {
  return _file_pos;
}
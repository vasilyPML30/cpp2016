#include "huffman.h"
#include <climits>
#include <algorithm>

BitReader::BitReader(const std::string &file_name):
                      _in_file(file_name.c_str()) {
  _buffer = _pos = 0;
}

BitReader &BitReader::operator>>(bool &bit) {
  if (_pos >= CHAR_BIT) {
    _buffer = _in_file.get();
    _pos = 0;
  }
  bit = _buffer & (1 << (CHAR_BIT - 1 - _pos++));
  return *this;
}

void BitReader::rewind() {
  HuffmanEncoder::rewind_istream(_in_file);
}

BitWriter::BitWriter(const std::string &file_name):
                     _out_file(file_name.c_str()) {
  _buffer = _pos = _file_pos = 0;
}

BitWriter::~BitWriter() {
  flush();
}

BitWriter &BitWriter::operator<<(bool bit) {
  if (_pos >= CHAR_BIT) {
    flush();
    _buffer = 0;
    _pos = 0;
  }
  _buffer |= (bit << (CHAR_BIT - 1 - _pos++));
  return *this;
}

BitWriter &BitWriter::operator<<(const std::vector<bool> &array) {
  for (std::size_t i = 0; i < array.size(); i++)
    *this << array[i];
  return *this;
}

BitWriter &BitWriter::operator<<(unsigned char symbol) {
  for (std::size_t i = 0; i < CHAR_BIT; i++)
    *this << (bool)(symbol & (1 << (CHAR_BIT - 1 - i)));
  return *this;
}

void BitWriter::flush() {
  if (_pos)
    _out_file.put(_buffer);
  _pos = 0;
  _file_pos++;
}

size_t BitWriter::tellg() const {
  return _file_pos;
}

TreeNode::TreeNode(std::pair<std::size_t, unsigned char> symbol) {
  _symbol = symbol.second;
  _frequency = symbol.first;
  _left = _right = NULL;
  _is_leaf = true;
}

TreeNode::TreeNode(TreeNode *left, TreeNode *right) {
  _left = left;
  _right = right;
  _is_leaf = false;
  update_frequency();
}

TreeNode::TreeNode() {
  _left = _right = NULL;
  _is_leaf = false;
  update_frequency();
}

TreeNode::~TreeNode() {
  std::cout << "delete Node (" <<_frequency << ")" << std::endl;
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
                              size_t &freq_pos) {
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
  if (node->is_leaf()) {
    _codes[node->get_symbol()] = code_prefix;
  }
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
    TreeNode *right = next_node(nodes_to_merge, frequencies, freq_pos);
    TreeNode *left = next_node(nodes_to_merge, frequencies, freq_pos);
    nodes_to_merge.push(new TreeNode(left, right));
  }
  _root = nodes_to_merge.front();
  _codes.resize(UCHAR_MAX);
  std::vector<bool> code_prefix;
  generate_codes(_root, code_prefix);
  std::cout << "encoding" << std::endl;
}

HuffTree::~HuffTree() {
  std::cout << "delete Tree" << std::endl;
  delete _root;
}


const std::vector<bool> &HuffTree::get_code(unsigned char symbol) const {
  return _codes[symbol];
}

void TreeNode::write_node(BitWriter &out_file) const {
  out_file << _is_leaf;
  if (_is_leaf) {
    out_file << _symbol;
  }
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
  return !item.first;
}

HuffmanEncoder::HuffmanEncoder(const std::string &file_name) :
                                  _in_file(file_name.c_str()) {
  std::vector< std::pair<std::size_t, unsigned char> > frequencies(UCHAR_MAX);
  while (true) {
    unsigned char symbol = _in_file.get();
    if (_in_file.eof())
      break;
    frequencies[symbol].second = symbol;
    frequencies[symbol].first++;
  }
  std::sort(frequencies.begin(), frequencies.end());
  frequencies.resize(std::remove_if(frequencies.begin(), frequencies.end(),
                     NeverPredicate()) - frequencies.begin());
  _tree = new HuffTree(frequencies);
  rewind_istream(_in_file);
}

HuffmanEncoder::~HuffmanEncoder() {
  std::cout << "delete Encoder" << std::endl;
  delete _tree;
}

void HuffmanEncoder::rewind_istream(std::istream &file) {
  file.clear();
  file.seekg(0, std::ios_base::beg);  
}

void HuffmanEncoder::encode(const std::string &file_name,
                            std::ostream &log) {
  BitWriter out_file(file_name);
  _tree->write_tree(out_file);
  out_file.flush();
  std::size_t extra_data_size = out_file.tellg();
  _in_file.seekg(std::ios_base::beg);
  std::size_t normal_size;
  while (true) {
    unsigned char symbol = _in_file.get();
    if (_in_file.eof())
      break;
    normal_size = _in_file.tellg();
    out_file << _tree->get_code(symbol);
  }
  out_file.flush();
  std::size_t compressed_size = (std::size_t)out_file.tellg() - extra_data_size;
  log << normal_size << std::endl;
  log << compressed_size << std::endl;
  log << extra_data_size << std::endl;
}

HuffmanDecoder::HuffmanDecoder(const std::string &file_name):
                                        _in_file(file_name) {
  _tree = new HuffTree(file_name);
}

HuffmanDecoder::~HuffmanDecoder() {
  delete _tree;
}

void HuffmanDecoder::decode(const std::string &file_name, std::ostream &log);  


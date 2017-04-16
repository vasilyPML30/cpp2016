#include "huffman.h"
#include <climits>
#include <algorithm>

BitReader::BitReader(const std::string &file_name):
                      _in_file(file_name.c_str()) {
  _buffer = _pos = 0;
  read_next_byte();
}

BitReader &BitReader::operator>>(bool &bit) {
  if (_pos >= CHAR_BIT)
    read_next_byte();
  bit = _buffer & (1 << (CHAR_BIT - 1 - _pos++));
  return *this;
}

BitReader &BitReader::operator>>(unsigned char &symbol) {
  symbol = 0;
  for (std::size_t i = 0; i < CHAR_BIT; i++) {
    bool bit;
    *this >> bit;
    symbol |= (bit << (CHAR_BIT - 1 - i));
  }
  return *this;
}

BitReader &BitReader::operator>>(unsigned int &number) {
  number = 0;
  std::size_t size = sizeof(number) * 8;
  for (std::size_t i = 0; i < size; i++) {
    bool bit;
    *this >> bit;
    number |= (bit << (size - 1 - i));
  }
  return *this;
}

std::size_t BitReader::tellg() {
  return _in_file.tellg();
}

void BitReader::read_next_byte() {
  _pos = 0;
  _buffer = _in_file.get();
}

BitWriter::BitWriter(const std::string &file_name):
                     _out_file(file_name.c_str()) {
  _buffer = _pos = 0;
}

BitWriter::~BitWriter() {
  flush();
}

BitWriter &BitWriter::operator<<(bool bit) {
  if (_pos >= CHAR_BIT) {
    flush();
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

BitWriter &BitWriter::operator<<(unsigned int number) {
  std::size_t size = sizeof(number) * 8;
  for (std::size_t i = 0; i < size; i++) {
    *this << (bool)(number & (1 << (size - 1 - i)));
  }
  return *this;
}

void BitWriter::flush() {
  if (_pos)
    _out_file.put(_buffer);
  _pos = _buffer = 0;
}

size_t BitWriter::tellp() {
  return _out_file.tellp();
}


void Utils::rewind_istream(std::istream &file) {
  file.clear();
  file.seekg(0, std::ios_base::beg);  
}

unsigned int Utils::bits_to_bytes(unsigned int bits_count) {
  return (bits_count + 7) / 8;
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

TreeNode::TreeNode(BitReader &in_file) {
  in_file >> _is_leaf;
  if (_is_leaf) {
    in_file >> _symbol;
    _left = _right = NULL;
  }
  else {
    _left = new TreeNode(in_file);
    _right = new TreeNode(in_file);
  }
}

TreeNode::~TreeNode() {
  delete _left;
  delete _right;
}

TreeNode *TreeNode::get_left() const {
  return _left;
}

TreeNode *TreeNode::get_right() const {
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

void HuffTree::generate_codes(const TreeNode *node,
                              std::vector<bool> &code_prefix) {
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

HuffTree::HuffTree(const std::vector< std::pair<std::size_t, unsigned char> >
                                                              &frequencies) {
  std::size_t freq_pos = 0;
  std::queue<TreeNode *> nodes_to_merge;
  _tree_size = frequencies.size();
  while (nodes_to_merge.size() + frequencies.size() - freq_pos > 1) {
    TreeNode *right = next_node(nodes_to_merge, frequencies, freq_pos);
    TreeNode *left = next_node(nodes_to_merge, frequencies, freq_pos);
    nodes_to_merge.push(new TreeNode(left, right));
    _tree_size++;
  }
  _root = nodes_to_merge.front();
  _codes.resize(UCHAR_MAX + 1);
  std::vector<bool> code_prefix;
  generate_codes(_root, code_prefix);
}

HuffTree::HuffTree(BitReader &in_file) {
  _root = new TreeNode(in_file);
}

HuffTree::~HuffTree() {
  delete _root;
}


const std::vector<bool> &HuffTree::get_code(unsigned char symbol) const {
  return _codes[symbol];
}

std::size_t HuffTree::tree_size() const {
  return _tree_size;
}

unsigned char HuffTree::get_symbol(BitReader &in_file) const {
  TreeNode *node = _root;
  while (!node->is_leaf()) {
    bool direction;
    in_file >> direction;
    if (!direction)
      node = node->get_left();
    else
      node = node->get_right();
  }
  return node->get_symbol();
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
                  (const std::pair<std::size_t, unsigned char>& item) const {
  return !item.first;
}

HuffmanEncoder::HuffmanEncoder(const std::string &file_name) :
                                  _in_file(file_name.c_str()) {
  std::vector< std::pair<std::size_t, unsigned char> >
                                    frequencies(UCHAR_MAX + 1);
  _normal_size = 0;
  while (true) {
    unsigned char symbol = _in_file.get();
    if (_in_file.eof())
      break;
    _normal_size = _in_file.tellg() * 8;
    frequencies[symbol].second = symbol;
    frequencies[symbol].first++;
  }
  std::sort(frequencies.begin(), frequencies.end());
  frequencies.resize(std::remove_if(frequencies.begin(), frequencies.end(),
                     NeverPredicate()) - frequencies.begin());
  _tree = new HuffTree(frequencies);
  _extra_data_size = _tree->tree_size() + frequencies.size() * CHAR_BIT +
                     1 + 3 * 8 * sizeof(unsigned int);
  _compressed_size = 0;
  for (size_t i = 0; i < frequencies.size(); i++)
    _compressed_size += _tree->get_code(frequencies[i].second).size()
                        * frequencies[i].first;
  _need_compression = (Utils::bits_to_bytes(_extra_data_size) +
                       Utils::bits_to_bytes(_compressed_size) <
                       Utils::bits_to_bytes(_normal_size));
}

HuffmanEncoder::~HuffmanEncoder() {
  delete _tree;
}

void HuffmanEncoder::encode(const std::string &file_name, std::ostream &log) {
  BitWriter out_file(file_name);
  out_file << _need_compression;
  out_file << _normal_size;
  if (_need_compression) {
    out_file << _extra_data_size;
    out_file << _compressed_size;
    _tree->write_tree(out_file);
  }
  out_file.flush();
  Utils::rewind_istream(_in_file);
  while (true) {
    unsigned char symbol = _in_file.get();
    if (_in_file.eof())
      break;
    if (_need_compression)
      out_file << _tree->get_code(symbol);
    else
      out_file << symbol;
  }
  out_file.flush();
  log << Utils::bits_to_bytes(_normal_size) << std::endl;
  if (_need_compression) {
    log << Utils::bits_to_bytes(_compressed_size) << std::endl;
    log << Utils::bits_to_bytes(_extra_data_size) << std::endl;
  }
  else {
    log << Utils::bits_to_bytes(_normal_size) << std::endl;
    log << 1 + sizeof(unsigned int) << std::endl;
  }
}

HuffmanDecoder::HuffmanDecoder(const std::string &file_name):
                                        _in_file(file_name) {
  _in_file >> _was_compressed;
  _in_file >> _normal_size;
  if (_was_compressed) {
    _in_file >> _extra_data_size;
    _in_file >> _compressed_size;
    _tree = new HuffTree(_in_file);
  }
  else {
    _tree = NULL;
    _compressed_size = _normal_size;
    _extra_data_size = 1 + 8 * sizeof(unsigned int);
  }
  _in_file.read_next_byte();
}

HuffmanDecoder::~HuffmanDecoder() {
  delete _tree;
}

void HuffmanDecoder::decode(const std::string &file_name, std::ostream &log) {
  std::ofstream out_file(file_name.c_str()); 
  for (std::size_t i = 0; i < Utils::bits_to_bytes(_normal_size); i++) {
    unsigned char symbol;
    if (_was_compressed) {
      symbol = _tree->get_symbol(_in_file);
    }
    else {
      _in_file >> symbol;
    }
    out_file.put(symbol);
  }
  log << Utils::bits_to_bytes(_extra_data_size) +
         Utils::bits_to_bytes(_compressed_size) << std::endl;
  log << Utils::bits_to_bytes(_normal_size) << std::endl;
  log << Utils::bits_to_bytes(_extra_data_size) << std::endl;
}
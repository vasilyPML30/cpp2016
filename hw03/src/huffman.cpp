#include "huffman.h"
#include <climits>
#include <algorithm>

void rewind_istream(std::istream &file) {
  file.clear();
  file.seekg(0, std::ios_base::beg);  
}

uint32_t bits_to_bytes(uint32_t bits_count) {
  return (bits_count + 7) / 8;
}

HuffmanTree::TreeNode::TreeNode(std::pair<std::size_t, unsigned char> symbol) {
  _symbol = symbol.second;
  _frequency = symbol.first;
  _left = _right = NULL;
}

HuffmanTree::TreeNode::TreeNode(TreeNode *left, TreeNode *right) {
  _left = left;
  _right = right;
  _frequency = _left->_frequency + _right->_frequency;
}

HuffmanTree::TreeNode::TreeNode(BitReader &in_file) {
  bool has_no_children;
  in_file >> has_no_children;
  if (has_no_children) {
    unsigned char tmp_symbol;
    in_file >> tmp_symbol;
    _left = _right = NULL;
    _symbol = tmp_symbol;
  }
  else {
    TreeNode *tmp_left = new TreeNode(in_file);
    TreeNode *tmp_right = new TreeNode(in_file);
    if (!tmp_left || !tmp_right) {
      throw std::bad_alloc();
    }
    _left = tmp_left;
    _right = tmp_right;
  }
}

HuffmanTree::TreeNode::~TreeNode() {
  delete _left;
  delete _right;
}

HuffmanTree::TreeNode *HuffmanTree::TreeNode::get_left() const {
  return _left;
}

HuffmanTree::TreeNode *HuffmanTree::TreeNode::get_right() const {
  return _right;
}

bool HuffmanTree::TreeNode::is_leaf() const {
  return !_left && !_right;
}

unsigned char HuffmanTree::TreeNode::get_symbol() const {
  return _symbol;
}

bool HuffmanTree::TreeNode::operator<(const TreeNode &node) const {
   return _frequency < node._frequency;
}

HuffmanTree::TreeNode *HuffmanTree::next_node(
                              std::queue<TreeNode *> &nodes_to_merge,
                              const std::vector< std::pair<std::size_t,
                              unsigned char> > &frequencies,
                              size_t &freq_pos) {
  TreeNode *node1 = NULL, *node2 = NULL, *result = NULL;
  if (nodes_to_merge.empty() && freq_pos < frequencies.size()) {
    result = node1 = new TreeNode(frequencies[freq_pos]);
    if (!node1) {
      throw std::bad_alloc();
    }
  }
  else if (!nodes_to_merge.empty() && freq_pos >= frequencies.size()) {
    result = node2 = nodes_to_merge.front();
  }
  else {
    node1 = new TreeNode(frequencies[freq_pos]);
    if (!node1) {
      throw std::bad_alloc();
    }
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

void HuffmanTree::generate_codes(const TreeNode *node,
                              std::vector<bool> &code_prefix) {
  if (node->is_leaf()) {
    _codes[node->get_symbol()] =
          (node == _root ? std::vector<bool>(1) : code_prefix);
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

HuffmanTree::HuffmanTree(const std::vector<
                               std::pair<std::size_t, unsigned char> >
                                                         &frequencies) {
  std::size_t freq_pos = 0;
  std::queue<TreeNode *> nodes_to_merge;
  _tree_size = frequencies.size();
  while (nodes_to_merge.size() + frequencies.size() - freq_pos > 1) {
    TreeNode *right = next_node(nodes_to_merge, frequencies, freq_pos);
    TreeNode *left = next_node(nodes_to_merge, frequencies, freq_pos);
    nodes_to_merge.push(new TreeNode(left, right));
    if (!nodes_to_merge.back()) {
      throw std::bad_alloc();
    }
    _tree_size++;
  }
  _root = next_node(nodes_to_merge, frequencies, freq_pos);
  _codes.resize(UCHAR_MAX + 1);
  std::vector<bool> code_prefix;
  generate_codes(_root, code_prefix);
}

HuffmanTree::HuffmanTree(BitReader &in_file) {
  _root = new TreeNode(in_file);
  if (!_root) {
    throw std::bad_alloc();
  }
}

HuffmanTree::~HuffmanTree() {
  delete _root;
}


const std::vector<bool> &HuffmanTree::get_code(unsigned char symbol) const {
  return _codes[symbol];
}

std::size_t HuffmanTree::tree_size() const {
  return _tree_size;
}

unsigned char HuffmanTree::get_symbol(BitReader &in_file) const {
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

void HuffmanTree::TreeNode::write_node(BitWriter &out_file) const {
  out_file << is_leaf();
  if (is_leaf()) {
    out_file << _symbol;
  }
  else {
    _left->write_node(out_file);
    _right->write_node(out_file);
  }
}

void HuffmanTree::write_tree(BitWriter &out_file) const {
  _root->write_node(out_file);
}

bool HuffmanEncoder::NeverPredicate::operator()
                  (const std::pair<std::size_t, unsigned char>& item) const {
  return !item.first;
}

HuffmanEncoder::HuffmanEncoder(const std::string &file_name) :
                                  _in_file(file_name.c_str()) {
  if (!_in_file) {
    throw std::ios_base::failure("can not open input file");
  }
  _in_file.exceptions(std::ios_base::eofbit | std::ios_base::badbit);
  std::vector< std::pair<std::size_t, unsigned char> >
                                    frequencies(UCHAR_MAX + 1);
  uint32_t tmp_normal_size = 0;
  while (true) {
    unsigned char symbol;
    try {
      symbol = _in_file.get();
    }
    catch (std::ios_base::failure error) {
      if (_in_file.eof()) {
        break;
      }
      else {
        throw error;
      }
    }
    tmp_normal_size = _in_file.tellg() * 8;
    frequencies[symbol].second = symbol;
    frequencies[symbol].first++;
  }
  if (!tmp_normal_size) {
    _normal_size = 0;
    _need_compression = false;
    _tree = NULL;
  }
  else {
    std::sort(frequencies.begin(), frequencies.end());
    frequencies.resize(std::remove_if(frequencies.begin(), frequencies.end(),
                       NeverPredicate()) - frequencies.begin());
    _tree = new HuffmanTree(frequencies);
    if (!_tree) {
      throw std::bad_alloc();
    }
    _normal_size = tmp_normal_size;
    _extra_data_size = _tree->tree_size() + frequencies.size() * CHAR_BIT +
                       1 + 3 * 8 * sizeof(uint32_t);
    _compressed_size = 0;
    for (size_t i = 0; i < frequencies.size(); i++)
      _compressed_size += _tree->get_code(frequencies[i].second).size()
                          * frequencies[i].first;
    _need_compression = (bits_to_bytes(_extra_data_size) +
                         bits_to_bytes(_compressed_size) <
                         bits_to_bytes(_normal_size));
  }
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
  rewind_istream(_in_file);
  while (true) {
    unsigned char symbol;
    try {
      symbol = _in_file.get();
    }
    catch (std::ios_base::failure error) {
      if (_in_file.eof()) {
        break;
      }
      else {
        throw error;
      }
    }
    if (_need_compression)
      out_file << _tree->get_code(symbol);
    else
      out_file << symbol;
  }
  out_file.flush();
  log << bits_to_bytes(_normal_size) << std::endl;
  if (_need_compression) {
    log << bits_to_bytes(_compressed_size) << std::endl;
    log << bits_to_bytes(_extra_data_size) << std::endl;
  }
  else {
    log << bits_to_bytes(_normal_size) << std::endl;
    log << 1 + sizeof(uint32_t) << std::endl;
  }
}

HuffmanDecoder::HuffmanDecoder(const std::string &file_name):
                                        _in_file(file_name) {
  bool tmp_was_compressed;
  uint32_t tmp_normal_size;
  uint32_t tmp_extra_data_size;
  uint32_t tmp_compressed_size;
  HuffmanTree *tmp_tree;

  _in_file >> tmp_was_compressed;
  _in_file >> tmp_normal_size;
  if (tmp_was_compressed) {
    _in_file >> tmp_extra_data_size;
    _in_file >> tmp_compressed_size;
    tmp_tree = new HuffmanTree(_in_file);
    if (!tmp_tree) {
      throw std::bad_alloc();
    }
  }
  else {
    tmp_tree = NULL;
    tmp_compressed_size = tmp_normal_size;
    tmp_extra_data_size = 1 + 8 * sizeof(uint32_t);
  }
  if (tmp_normal_size) {
    _in_file.read_next_byte();
  }
  _was_compressed = tmp_was_compressed;
  _normal_size = tmp_normal_size;
  _extra_data_size = tmp_extra_data_size;
  _compressed_size = tmp_compressed_size;
  _tree = tmp_tree;
}

HuffmanDecoder::~HuffmanDecoder() {
  delete _tree;
}

void HuffmanDecoder::decode(const std::string &file_name, std::ostream &log) {
  std::ofstream out_file(file_name.c_str());
  if (!out_file) {
    throw std::ios_base::failure("can not open output file");
  }
  out_file.exceptions(std::ios_base::eofbit | std::ios_base::badbit);
  for (std::size_t i = 0; i < bits_to_bytes(_normal_size); i++) {
    unsigned char symbol;
    if (_was_compressed) {
      symbol = _tree->get_symbol(_in_file);
    }
    else {
      _in_file >> symbol;
    }
    out_file.put(symbol);
  }
  log << bits_to_bytes(_extra_data_size) +
         bits_to_bytes(_compressed_size) << std::endl;
  log << bits_to_bytes(_normal_size) << std::endl;
  log << bits_to_bytes(_extra_data_size) << std::endl;
}
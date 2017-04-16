#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>

class BitReader {
public:
  BitReader(const std::string &file_name);

  BitReader &operator>>(bool &bit);
  BitReader &operator>>(unsigned char &symbol);
  BitReader &operator>>(unsigned int &number);

  std::size_t tellg();
  void read_next_byte();

private:
  BitReader(const BitReader &t);
  BitReader &operator=(const BitReader &t);

  unsigned char _buffer;
  std::ifstream _in_file;
  std::size_t _pos;
};

class BitWriter {
public:
  BitWriter(const std::string &file_name);
  ~BitWriter();

  BitWriter &operator<<(bool bit);
  BitWriter &operator<<(const std::vector<bool> &array);
  BitWriter &operator<<(unsigned char symbol);
  BitWriter &operator<<(unsigned int number);

  void flush();
  size_t tellp();

private:
  BitWriter(const BitWriter &t);
  BitWriter &operator=(const BitWriter &t);

  unsigned char _buffer;
  std::ofstream _out_file;
  std::size_t _pos;
};

class Utils {
public:
  static void rewind_istream(std::istream &file);
  static unsigned int bits_to_bytes(unsigned int bits_count);
};

class TreeNode {
public:
  TreeNode(std::pair<std::size_t, unsigned char> sybmol);
  TreeNode(TreeNode *left, TreeNode *right);
  TreeNode(BitReader &in_file);
  ~TreeNode();

  TreeNode *get_left() const;
  TreeNode *get_right() const;
  bool is_leaf() const;
  unsigned char get_symbol() const; 
  bool operator<(const TreeNode &node) const;
  void write_node(BitWriter &out_file) const;

private:
  TreeNode(const TreeNode &t);
  TreeNode &operator=(const TreeNode &t);

  void update_frequency();

  bool _is_leaf;
  unsigned char _symbol;
  int _frequency;
  TreeNode *_left, *_right;
};

class HuffTree {
public:
  HuffTree(const std::vector< std::pair<std::size_t, unsigned char> >
                                                        &frequencies);
  HuffTree(BitReader &in_file);
  ~HuffTree();

  const std::vector<bool> &get_code(unsigned char symbol) const;
  unsigned char get_symbol(BitReader &in_file) const;
  void write_tree(BitWriter &out_file);
  std::size_t tree_size() const;

private:
  HuffTree(const HuffTree &t);
  HuffTree &operator=(const HuffTree &t);

  TreeNode *next_node(
            std::queue<TreeNode *> &nodes_to_merge,
            const std::vector< std::pair<std::size_t, unsigned char> >
                                       &frequencies, size_t &freq_pos);
  void generate_codes(const TreeNode *node, std::vector<bool> &code_prefix);
  
  std::vector< std::vector<bool> > _codes;
  TreeNode *_root;
  size_t _tree_size;
};

class HuffmanEncoder {
public:
  HuffmanEncoder(const std::string &file_name);
  ~HuffmanEncoder();

  void encode(const std::string &file_name, std::ostream &log);
  
  class NeverPredicate {
  public:
    bool operator()(const std::pair<std::size_t, unsigned char> &item) const;
  };

private:
  HuffmanEncoder(const HuffmanEncoder &t);
  HuffmanEncoder &operator=(const HuffmanEncoder &t);

  HuffTree *_tree;
  std::ifstream _in_file;
  unsigned int _normal_size;
  unsigned int _compressed_size;
  unsigned int _extra_data_size;
  bool _need_compression;
};

class HuffmanDecoder {
public:
  HuffmanDecoder(const std::string &file_name);
  ~HuffmanDecoder();
  
  void decode(const std::string &file_name, std::ostream &log);  

private:
  HuffmanDecoder(const HuffmanDecoder &t);
  HuffmanDecoder &operator=(const HuffmanDecoder &t);
  
  HuffTree *_tree;
  BitReader _in_file;
  unsigned int _normal_size;
  unsigned int _compressed_size;
  unsigned int _extra_data_size;
  bool _was_compressed;
};

#endif
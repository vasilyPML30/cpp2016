#ifndef HUFFMAN_H_
#define HUFFMAN_H_

#include "bitstream.h"

#include <vector>
#include <string>
#include <fstream>
#include <queue>

typedef unsigned int uint32_t;

class HuffmanTree {
public:
  HuffmanTree(const std::vector< std::pair<std::size_t, unsigned char> >
                                                        &frequencies);
  HuffmanTree(BitReader &in_file);
  ~HuffmanTree();

  const std::vector<bool> &get_code(unsigned char symbol) const;
  unsigned char get_symbol(BitReader &in_file) const;
  void write_tree(BitWriter &out_file) const;
  std::size_t tree_size() const;

private:
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

    unsigned char _symbol;
    int _frequency;
    TreeNode *_left, *_right;
  };

  HuffmanTree(const HuffmanTree &t);
  HuffmanTree &operator=(const HuffmanTree &t);

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
  class NeverPredicate {
  public:
    bool operator()(const std::pair<std::size_t, unsigned char> &item) const;
  };

  HuffmanEncoder(const std::string &file_name);
  ~HuffmanEncoder();

  void encode(const std::string &file_name, std::ostream &log);
  
private:
  HuffmanEncoder(const HuffmanEncoder &t);
  HuffmanEncoder &operator=(const HuffmanEncoder &t);

  HuffmanTree *_tree;
  std::ifstream _in_file;
  uint32_t _normal_size;
  uint32_t _compressed_size;
  uint32_t _extra_data_size;
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
  
  HuffmanTree *_tree;
  BitReader _in_file;
  uint32_t _normal_size;
  uint32_t _compressed_size;
  uint32_t _extra_data_size;
  bool _was_compressed;
};

void rewind_istream(std::istream &file);
uint32_t bits_to_bytes(uint32_t bits_count);

#endif
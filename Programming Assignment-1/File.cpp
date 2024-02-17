#include "File.h"


Block File::getBlock(int index) const
{
	/* TODO */
	if(blocks.getSize()>index) return blocks.getNodeAtIndex(index)->data;

	else{
		Block empty_block("");
		return empty_block;
	}
}

size_t File::fileSize() const
{
	/* TODO */
	Node<Block> *temp = blocks.getFirstNode();
	if (temp) {
		size_t result=temp->data.getSize(); 
		temp=temp->next;
		while(temp) {
			result+=temp->data.getSize();
			temp=temp->next; } 
		return result;}
	else return 0;
}

int File::numBlocks() const
{
	/* TODO */
	if(blocks.isEmpty()) return 0;
	else return blocks.getSize();

}

bool File::isEmpty() const
{
	/* TODO */
	if(blocks.isEmpty()) return true;
	else return false;
	
}

bool File::operator==(const File &rhs) const
{
	/* TODO */
	if(numBlocks()!=rhs.numBlocks()) return false;
	else { 	
		Node<Block> *temp = blocks.getFirstNode();
		Node<Block> *other= rhs.blocks.getFirstNode();
		while(temp && other) {
			if(!(temp->data==other->data)) return false;
			temp=temp->next;
			other=other->next;
		}
		return true;	
	}
	
}

void File::newBlock(const Block &block)
{
	/* TODO */
	blocks.append(block);
}

void File::removeBlock(int index)
{
	/* TODO */
	blocks.removeNodeAtIndex(index);
}

void File::mergeBlocks(int sourceIndex, int destIndex)
{
	/* TODO */
	if(0 >sourceIndex || sourceIndex > numBlocks()-1 || 0 >destIndex || destIndex > numBlocks()-1) return;
	Node<Block> *source= blocks.getNodeAtIndex(sourceIndex);
	Node<Block> *dest= blocks.getNodeAtIndex(destIndex);
    dest->data = dest->data + source->data;
    blocks.removeNodeAtIndex(sourceIndex);
}

void File::printContents() const{
	if(isEmpty()){
		std::cout << "File is empty" << std::endl;
	}
	else{
		for(int i = 0; i < blocks.getSize(); i++){
			Node<Block> *block = blocks.getNodeAtIndex(i);
			std::cout << block->data.getContent();
		}
		std::cout << std::endl << fileSize() << std::endl;
	}
}
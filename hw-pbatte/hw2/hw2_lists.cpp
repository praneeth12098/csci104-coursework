#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Item 
{
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
};

Item* concatenate(Item* head1, Item* head2);  // returns head pointer to new list
void removeEvens(Item*& head);
double findAverage(Item* head); // return 0.0 if the list is empty
double findAveragecount(Item* head, int &count);
void readLists(const char* filename, Item*& head1, Item*& head2);
void printList(std::ostream& ofile, Item* head);

void deallocate_memory(Item* head)
{
	Item* temp;
	while(head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

void readLists(const char* filename, Item*& head1, Item*& head2)
{
	ifstream myfile(filename);

	string nums;
	if(myfile)
	{
		getline(myfile, nums);
		stringstream ss(nums);
		int v;

		ss >> v;
		Item* temp1 = new Item(v, NULL);
		head1 = temp1;

		while(ss >> v)
		{
			while(temp1->next)
			{
				temp1 = temp1->next;
			}
			Item* ptr = new Item(v, NULL);
			temp1->next = ptr;
		}

		getline(myfile, nums);
		stringstream sss(nums);

		sss >> v;
		Item* temp2 = new Item(v, NULL);
		head2 = temp2;

		while(sss >> v)
		{
			while(temp2->next)
			{
				temp2 = temp2->next;
			}
			Item* ptr = new Item(v, NULL);
			temp2->next = ptr;
		}

		//deallocate_memory(temp1);
		//deallocate_memory(temp2);
	}
}

Item* concatenate(Item* head1, Item* head2)
{
	Item* temp1 = head1;
	Item* temp2 = head2;
	Item* result = head1;
	
	if(temp1 == NULL)
	 	return temp2;
	if(temp2 == NULL)
	 	return temp1;

	result->next = concatenate(temp1->next, temp2);

	return result;
}

void removeEvens(Item*& head)
{
	Item* temp = head;

	if(temp->next == NULL)
		return;
	if(temp->val % 2 == 0)
	{
		head = temp->next;
	}
	if(temp->next->val % 2 == 0)
	{
		temp->next = temp->next->next;
		removeEvens(temp);
	}
	else
	{
		temp = temp->next;
		removeEvens(temp);
	}
}

double findAverage(Item* head)
{
	int count = 0;
	int sum;

	if(head == NULL)
		return 0.0;

	sum = findAveragecount(head, count);
	return (double)sum/count;
}

double findAveragecount(Item* head, int &count)
{
	Item* temp = head;
	if(temp == NULL)
	{
		return 0.0;
	}
	else
	{
		count++;
		return temp->val + findAveragecount(temp->next, count);
	}
}

void printList(std::ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);   
  }
}

int main(int argc, char* argv[])
{
	Item* list1 = NULL;
	Item* list2 = NULL;
	Item* list3 = NULL;
	
	ofstream ofile("output.txt");

	readLists(argv[1], list1, list2);
	list3 = concatenate(list1, list2);
	printList(ofile, list3);
	removeEvens(list3);
	printList(ofile, list3);
	double x = findAverage(list3);
	printList(ofile, list3);
	ofile << x;

	deallocate_memory(list1);
	deallocate_memory(list2);
	deallocate_memory(list3);
}
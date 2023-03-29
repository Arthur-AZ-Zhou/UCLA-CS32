Winter 2023 CS 32
Homework 4
Time due: 11:00 PM Tuesday, March 7

We anticipate that many people working on Project 3 will spend a lot of time debugging something that arises from a common novice misunderstanding. To save you that time later, we'll give you a chance to make that mistake in a simpler context, so you can work out that issue and how it manifests itself. (It may turn out that you don't have that misunderstanding, so you won't have any issues doing this problem. Still, keep this problem in mind, because you may still make the mistake in Project 3.)

Be especially sure to run your code for this problem under g32 to help ensure that there are no pointer/iterator violations or memory leaks that common misunderstandings may lead to.

Material about vectors, lists, and iterators are in lecture09-updated.pptx in the slides for lecture 1 and the STL lecture and STL slides for lectures 2&3.

Implement the removeOdd function; you must use list's erase member function; you must not use lists's remove or remove_if member functions. Each int in the list must be examined for oddness no more than once.
	#include <list>
	#include <vector>
	#include <algorithm>
	#include <iostream>
	#include <cassert>
	using namespace std;

	  // Remove the odd integers from li.
	  // It is acceptable if the order of the remaining even integers is not
	  // the same as in the original list.
	void removeOdd(list<int>& li)
	{
	}

	void test()
	{
	    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	    list<int> x(a, a+8);  // construct x from the array
	    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	    removeOdd(x);
	    assert(x.size() == 4);
	    vector<int> v(x.begin(), x.end());  // construct v from x
	    sort(v.begin(), v.end());
	    int expect[4] = { 2, 4, 6, 8 };
	    for (int k = 0; k < 4; k++)
	        assert(v[k] == expect[k]);
	}

	int main()
	{
	    test();
	    cout << "Passed" << endl;
	}
For this problem, you will turn a file named oddlist.cpp with the body of the removeOdd function, from its "void" to its "}", no more and no less. Your function must compile and work correctly when substituted into the program above, leaking no memory.

Implement the removeOdd function; you must use vector's erase member function. Each int in the vector must be examined for oddness no more than once.
	#include <vector>
	#include <algorithm>
	#include <iostream>
	#include <cassert>
	using namespace std;

	  // Remove the odd integers from v.
	  // It is acceptable if the order of the remaining even integers is not
	  // the same as in the original vector.
	void removeOdd(vector<int>& v)
	{
	}

	void test()
	{
	    int a[8] = { 2, 8, 5, 6, 7, 3, 4, 1 };
	    vector<int> x(a, a+8);  // construct x from the array
	    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
	    removeOdd(x);
	    assert(x.size() == 4);
	    sort(x.begin(), x.end());
	    int expect[4] = { 2, 4, 6, 8 };
	    for (int k = 0; k < 4; k++)
	        assert(x[k] == expect[k]);
	}

	int main()
	{
	    test();
	    cout << "Passed" << endl;
	}
For this problem, you will turn a file named oddvector.cpp with the body of the removeOdd function, from its "void" to its "}", no more and no less. Your function must compile and work correctly when substituted into the program above, leaking no memory.

Implement the removeBad function; you must use list's erase member function; you must not use lists's remove or remove_if member functions. Each Movie in the list must have its rating examined no more than once.
	#include <list>
	#include <vector>
	#include <algorithm>
	#include <iostream>
	#include <cassert>
	using namespace std;

	vector<int> destroyedOnes;

	class Movie
	{
	  public:
	    Movie(int r) : m_rating(r) {}
	    ~Movie() { destroyedOnes.push_back(m_rating); }
	    int rating() const { return m_rating; }
	  private:
	    int m_rating;
	};

	  // Remove the movies in li with a rating below 50 and destroy them.
	  // It is acceptable if the order of the remaining movies is not
	  // the same as in the original list.
	void removeBad(list<Movie*>& li)
	{
	}

	void test()
	{
	    int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	    list<Movie*> x;
	    for (int k = 0; k < 8; k++)
	        x.push_back(new Movie(a[k]));
	    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
	    removeBad(x);
	    assert(x.size() == 4 && destroyedOnes.size() == 4);
	    vector<int> v;
	    for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
	    {
	        Movie* mp = *p;
	        v.push_back(mp->rating());
	    }
	      // Aside:  Since C++11, the above loop could be
	      //     for (auto p = x.begin(); p != x.end(); p++)
	      //     {
	      //         Movie* mp = *p;
	      //         v.push_back(mp->rating());
	      //     }
	      // or    
	      //     for (auto p = x.begin(); p != x.end(); p++)
	      //     {
	      //         auto mp = *p;
	      //         v.push_back(mp->rating());
	      //     }
	      // or    
	      //     for (Movie* mp : x)
	      //         v.push_back(mp->rating());
	      // or    
	      //     for (auto mp : x)
	      //         v.push_back(mp->rating());
	    sort(v.begin(), v.end());
	    int expect[4] = { 70, 80, 85, 90 };
	    for (int k = 0; k < 4; k++)
	        assert(v[k] == expect[k]);
	    sort(destroyedOnes.begin(), destroyedOnes.end());
	    int expectGone[4] = { 10, 15, 20, 30 };
	    for (int k = 0; k < 4; k++)
	        assert(destroyedOnes[k] == expectGone[k]);
	    for (list<Movie*>::iterator p = x.begin(); p != x.end(); p++)
	        delete *p;
	}

	int main()
	{
	    test();
	    cout << "Passed" << endl;
	}
For this problem, you will turn a file named badlist.cpp with the body of the removeBad function, from its "void" to its "}", no more and no less. Your function must compile and work correctly when substituted into the program above, leaking no memory.

Implement the removeBad function; you must use vector's erase member function. Each Movie in the vector must have its rating examined no more than once.
	#include <vector>
	#include <algorithm>
	#include <iostream>
	#include <cassert>
	using namespace std;

	vector<int> destroyedOnes;

	class Movie
	{
	  public:
	    Movie(int r) : m_rating(r) {}
	    ~Movie() { destroyedOnes.push_back(m_rating); }
	    int rating() const { return m_rating; }
	  private:
	    int m_rating;
	};

	  // Remove the movies in v with a rating below 50 and destroy them.
	  // It is acceptable if the order of the remaining movies is not
	  // the same as in the original vector.
	void removeBad(vector<Movie*>& v)
	{
	}

	void test()
	{
	    int a[8] = { 85, 80, 30, 70, 20, 15, 90, 10 };
	    vector<Movie*> x;
	    for (int k = 0; k < 8; k++)
	        x.push_back(new Movie(a[k]));
	    assert(x.size() == 8 && x.front()->rating() == 85 && x.back()->rating() == 10);
	    removeBad(x);
	    assert(x.size() == 4 && destroyedOnes.size() == 4);
	    vector<int> v;
	    for (int k = 0; k < 4; k++)
	        v.push_back(x[k]->rating());
	    sort(v.begin(), v.end());
	    int expect[4] = { 70, 80, 85, 90 };
	    for (int k = 0; k < 4; k++)
	        assert(v[k] == expect[k]);
	    sort(destroyedOnes.begin(), destroyedOnes.end());
	    int expectGone[4] = { 10, 15, 20, 30 };
	    for (int k = 0; k < 4; k++)
	        assert(destroyedOnes[k] == expectGone[k]);
	    for (vector<Movie*>::iterator p = x.begin(); p != x.end(); p++)
	        delete *p;
	}

	int main()
	{
	    test();
	    cout << "Passed" << endl;
	}
For this problem, you will turn a file named badvector.cpp with the body of the removeBad function, from its "void" to its "}", no more and no less. Your function must compile and work correctly when substituted into the program above, leaking no memory.

Make sure you understand why the code below passes the first two tests but fails the third. Draw pictures if necessary. Don't forget the lesson you learn from this problem when working on Project 3.
#include <iostream>
#include <vector>
#include <list>
using namespace std;

const int MAGIC = 11223344;

void test()
{
    bool allValid = true;

    vector<int> v1(5, MAGIC);
    int k = 0;
    for ( ; k != v1.size(); k++)
    {
        if (v1[k] != MAGIC)
        {
            cout << "v1[" << k << "] is " << v1[k] << ", not " << MAGIC <<"!" << endl;
            allValid = false;
        }
        if (k == 2)
        {
            for (int i = 0; i < 5; i++)
                v1.push_back(MAGIC);
        }
    }
    if (allValid  &&  k == 10)
        cout << "Passed test 1" << endl;
    else
        cout << "Failed test 1" << endl;

    allValid = true;
    list<int> l1(5, MAGIC);
    k = 0;
    for (list<int>::iterator p = l1.begin(); p != l1.end(); p++, k++)
    {
        if (*p != MAGIC)
        {
            cout << "Item# " << k << " is " << *p << ", not " << MAGIC <<"!" << endl;
            allValid = false;
        }
        if (k == 2)
        {
            for (int i = 0; i < 5; i++)
                l1.push_back(MAGIC);
        }
    }
    if (allValid  &&  k == 10)
        cout << "Passed test 2" << endl;
    else
        cout << "Failed test 2" << endl;

    allValid = true;
    vector<int> v2(5, MAGIC);
    k = 0;
    for (vector<int>::iterator p = v2.begin(); p != v2.end(); p++, k++)
    {
        if (k >= 20)  // prevent infinite loop
            break;
        if (*p != MAGIC)
        {
            cout << "Item# " << k << " is " << *p << ", not " << MAGIC <<"!" << endl;
            allValid = false;
        }
        if (k == 2)
        {
            for (int i = 0; i < 5; i++)
                v2.push_back(MAGIC);
        }
    }
    if (allValid  &&  k == 10)
        cout << "Passed test 3" << endl;
    else
        cout << "Failed test 3" << endl;
}

int main()
{
    test();
}
Explain in a sentence or two what happens during the execution of test case 3 that eventually leads to test case 3 failing.

The files Set.h and Set.cpp contain the definition and implementation of Set implemented using a doubly-linked list. A client who wants to use a Set has to change the type alias declaration in Set.h, and within one source file, cannot have two Sets containing different types.

Eliminate the using statement defining the type alias, and change Set to be a class template, so that a client can say

	#include "Set.h"
	#include <string>
	using std::string;
	...
	Set<int> si;
	Set<string> ss;
	si.insert(34);
	ss.insert("34+35");
	...
Also, change unite and butNot to be function templates.

(Hint: Transforming the solution based on a type alias is a mechanical task that takes five minutes if you know what needs to be done. What makes this problem non-trivial for you is that you haven't done it before; the syntax for declaring templates is new to you, so you may not get it right the first time.)
(Hint: Template typename parameters don't have to be named with single letters like T; they can be names of your choosing. You might find that by choosing the name ItemType, you'll have many fewer changes to make.)

(Hint: The Node class nested in the Set class can talk about the template parameter of the Set class; it should not itself be a template class.)

The declarations and implementations of your Set class template and the unite and butNot template functions must be in just one file, Set.h, which is all that you will turn in for this problem. Although the implementation of a non-template non-inline function should not be placed in a header file (because of linker problems if that header file were included in multiple source files), the implementation of a template function, whether or not it's declared inline, can be in a header file without causing linker problems, and in fact the header file is the normal place to put it in most C++ environments.

There's a pre-C++20 language technicality that relates to a type declared inside a class template, like N below:

	template <typename T>
	class S
	{
	  ...
	  struct N
	  {
	    ...
	  };
	  N* f();
	  ...
	};
The technicality affects how we specify the return type of a function (such as S<T>::f) when that return type uses a type defined inside a template class (such as S<T>::N). If we attempt to implement f this way:

	template <typename T>
	S<T>::N* S<T>::f()    // Error!  Won't compile in C++17 or earlier.
	{
	  ...
	}
the pre-C++20 technicality requires the compiler to not recognize S<T>::N as a type name; it must be announced as a type name this way:

	template <typename T>
	typename S<T>::N* S<T>::f()    // OK in all C++ versions
	{
	  ...
	}
Giving g32 the -std=c++20 option will cause it to use C++20. We will test your code with C++17, unless it doesn't compile, in which case we'll test it with C++20 instead.

For you to not get a score of zero for this problem, this test program that we will try with your Set.h must build and execute successfully under both g32 and either Visual C++ or clang++, with no Set.cpp file on the command line (for g32) or as part of the project (for Visual C++ or Xcode):

	#include "Set.h"
	#include <iostream>
	#include <string>
	#include <cassert>
	using namespace std;

	void test()
	{
	    Set<int> si;
	    Set<string> ss;
	    assert(si.empty());
	    assert(ss.empty());
	    assert(si.size() == 0);
	    assert(ss.size() == 0);
	    assert(si.insert(10));
	    assert(ss.insert("hello"));
	    assert(si.contains(10));
	    assert(ss.contains("hello"));
	    int i;
	    assert(si.get(0, i)  &&  i == 10);
	    string s;
	    assert(ss.get(0, s)  &&  s == "hello");
	    assert(si.erase(10));
	    assert(ss.erase("hello"));
	    Set<int> si2(si);
	    Set<string> ss2(ss);
	    si.swap(si2);
	    ss.swap(ss2);
	    si = si2;
	    ss = ss2;
	    unite(si,si2,si);
	    unite(ss,ss2,ss);
	    butNot(si,si2,si);
	    butNot(ss,ss2,ss);
	}

	int main()
	{
	    test();
	    cout << "Passed all tests" << endl;
	}
Consider this program:

	#include "Set.h"  // class template from problem 2
	#include <string>
	using namespace std;

	class Coord
	{
	  public:
	    Coord(int r, int c) : m_row(r), m_col(c) {}
	    Coord() : m_row(0), m_col(0) {}
	    double r() const { return m_row; }
	    double c() const { return m_col; }
	  private:
	    double m_row;
	    double m_col;
	};

	int main()
	{
	    Set<int> si;
	    si.insert(7);               // OK
	    Set<string> ss;
	    ss.insert("7-Up");          // OK
	    Set<Coord> sc;
	    sc.insert(Coord(7, -7));    // error!
	}
Explain in a sentence or two why the call to Set<Coord>::insert causes at least one compilation error. (Notice that the calls to Set<int>::insert and Set<string>::insert are fine.) Don't just transcribe a compiler error message; your answer must indicate you understand the ultimate root cause of the problem and why that is connected to the call to Set<Coord>::insert.

A file has a name. A file is either a plain file (like a text file, an image file, a C++ source program, etc.) or a directory. Directories contain zero or more files. The following program reflects this structure:

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class File
{
  public:
    File(string nm) : m_name(nm) {}
    virtual ~File() {}
    string name() const { return m_name; }
    virtual bool add(File* f) = 0;
    virtual const vector<File*>* files() const = 0;
  private:
    string m_name;
};

class PlainFile : public File
{
  public:
    PlainFile(string nm) : File(nm) {}
    virtual bool add(File* f) { return false; }
    virtual const vector<File*>* files() const { return nullptr; }
};

class Directory : public File
{
  public:
    Directory(string nm) : File(nm) {}
    virtual ~Directory();
    virtual bool add(File* f) { m_files.push_back(f); return true; }
    virtual const vector<File*>* files() const { return &m_files; }
  private:
    vector<File*> m_files;
};

Directory::~Directory()
{
    for (int k = 0; k < m_files.size(); k++)
        delete m_files[k];
}

void listAll(string path, const File* f)  // two-parameter overload
{
    You will write this code.
}

void listAll(const File* f)  // one-parameter overload
{
    if (f != nullptr)
        listAll(f->name(), f);
}

int main()
{
    Directory* d1 = new Directory("Fun");
    d1->add(new PlainFile("party.jpg"));
    d1->add(new PlainFile("beach.jpg"));
    d1->add(new PlainFile("skitrip.jpg"));
    Directory* d2 = new Directory("Work");
    d2->add(new PlainFile("seaslab.jpg"));
    Directory* d3 = new Directory("My Pictures");
    d3->add(d1);
    d3->add(new PlainFile("me.jpg"));
    d3->add(new Directory("Miscellaneous"));
    d3->add(d2);
    listAll(d3);
    delete d3;
}
When the listAll function is called from the main routine above, the following output should be produced (the first line written is My Pictures, not an empty line):

My Pictures/
My Pictures/Fun/
My Pictures/Fun/party.jpg
My Pictures/Fun/beach.jpg
My Pictures/Fun/skitrip.jpg
My Pictures/me.jpg
My Pictures/Miscellaneous/
My Pictures/Work/
My Pictures/Work/seaslab.jpg
This is a list, one per line, of the complete pathname for listAll's argument and, if the argument is a directory, everything in that directory. A pathname has / separating pathname components, and the pathname of a directory ends with /.

You are to write the code for the two-parameter overload of listAll to make this happen. You must not use any additional container (such as a stack), and the two-parameter overload of listAll must be recursive. You must not use any global variables or variables declared with the keyword static, and you must not modify any of the code we have already written or add new functions. You may use a loop to traverse the vector; you must not use loops to avoid recursion.

Here's a useful function to know: The standard library string class has a + operator that concatenates strings and/or characters. For example,

	string s("Hello");
	string t("there");
	string u = s + ", " + t + '!';
	// Now u has the value "Hello, there!"
It's also useful to know that if you choose to traverse an STL container using some kind of iterator, then if the container is const, you must use a const_iterator:

	void f(const list<int>& c)  // c is const
	{
	    for (list<int>::const_iterator it = c.begin(); it != c.end(); it++)
	        cout << *it << endl;
	}
(Of course, a vector can be traversed either by using some kind of iterator, or by using operator[] with an integer argument).

For this problem, you will turn a file named list.cpp with the body of the two-parameter overload of the listAll function, from its "void" to its "}", no more and no less. Your function must compile and work correctly when substituted into the program above.

We introduced the two-parameter overload of listAll. Why could you not solve this problem given the constraints in part a if we had only a one-parameter listAll, and you had to implement it as the recursive function?

Suppose we have a list of N world cities, numbered from 0 to N-1. The two-dimensional array of doubles dist holds the airline distance between each pair of cities: dist[i][j] is the distance between city i and city j.

Now, for every pair of cities i and j, we'd like to consider all the flights between the two that make one stop in a third city k, and record which city k yields the shortest distance traveled in a one-stop flight between city i and city j that passes through city k. Here's the code:

	const int N = some value;
	assert(N > 2);  // algorithm fails if N <= 2
	double dist[N][N];
	...
	int bestMidPoint[N][N];
	for (int i = 0; i < N; i++)
	{
	    bestMidPoint[i][i] = -1;  // one-stop trip to self is silly
	    for (int j = 0; j < N; j++)
	    {
	        if (i == j)
	            continue;
	        int minDist = maximum possible integer;
	        for (int k = 0; k < N; k++)
	        {
	            if (k == i  ||  k == j)
	                continue;
	            int d = dist[i][k] + dist[k][j];
	            if (d < minDist)
	            {
	                minDist = d;
	                bestMidPoint[i][j] = k;
	            }
	        }
	    }
	}
What is the time complexity of this algorithm, in terms of the number of basic operations (e.g., additions, assignments, comparisons) performed: Is it O(N), O(N log N), or what? Why? (Note: In this homework, whenever we ask for the time complexity, we care only about the high order term, so don't give us answers like O(N2+4N).)

The algorithm in part a doesn't take advantage of the symmetry of distances: for every pair of cities i and j, dist[i][j] == dist[j][i]. We can skip a lot of operations and compute the best midpoints more quickly with this algorithm:

	const int N = some value;
	assert(N > 2);  // algorithm fails if N <= 2
	double dist[N][N];
	...
	int bestMidPoint[N][N];
	for (int i = 0; i < N; i++)
	{
	    bestMidPoint[i][i] = -1;  // one-stop trip to self is silly
	    for (int j = 0; j < i; j++)  // loop limit is now i, not N
	    {
	        int minDist = maximum possible integer;
	        for (int k = 0; k < N; k++)
	        {
	            if (k == i  ||  k == j)
	                continue;
	            int d = dist[i][k] + dist[k][j];
	            if (d < minDist)
	            {
	                minDist = d;
	                bestMidPoint[i][j] = k;
	                bestMidPoint[j][i] = k;
	            }
	        }
	    }
	}
What is the time complexity of this algorithm? Why?

Here again is the (non-template) non-member unite function for Sets from Set.cpp:

void unite(const Set& set1, const Set& set2, Set& result)
{
    const Set* sp = &set2;
    if (&result == &set1)
    {
        if (&result == &set2)
                return;
    }
    else if (&result == &set2)
        sp = &set1;
    else
    {
        result = set1;
        if (&set1 == &set2)
            return;
    }
    for (int k = 0; k < sp->size(); k++)
    {
        ItemType v;
        sp->get(k, v);
        result.insert(v);
    }
}
Assume that set1, set2, and the old value of result each have N elements. In terms of the number of linked list nodes visited during the execution of this function, what is its worst case time complexity? Why?

Here is an implementation of a related member function. The call

s3.unite(s1,s2);
sets s3 to the set union of s1 and s2. The implementation is

void Set::unite(const Set& set1, const Set& set2)
{
    vector<ItemType> v;

      // copy all items into v;
    for (Node* p1 = set1.m_head->m_next; p1 != set1.m_head; p1 = p1->m_next)
        v.push_back(p1->m_value);
    for (Node* p2 = set2.m_head->m_next; p2 != set2.m_head; p2 = p2->m_next)
        v.push_back(p2->m_value);

      // sort v using an O(N log N) algorithm
    sort(v.begin(), v.end());

      // delete result nodes (other than the dummy node)
    while (m_head->m_next != m_head)
        doErase(m_head->m_next);

      // copy unique items from v into result
    for (size_t k = 0; k < v.size(); k++)
    {
        if (k == 0  ||  v[k] != v[k-1])  // add non-duplicates
            insertBefore(m_head, v[k]);
    }

      // v is destroyed when function returns
}
Assume that set1, set2, and the old value of *this each have N elements. In terms of the number of linked list nodes or ItemType objects visited during the execution of this function, what is its time complexity? Why?

Here is a different implementation of the member function of part b:

void Set::unite(const Set& set1, const Set& set2)
{
    const Set* sp = &set2;
    if (this == &set1)
    {
        if (this == &set2)
                return;
    }
    else if (this == &set2)
        sp = &set1;
    else
    {
        *this = set1;
        if (&set1 == &set2)
            return;
    }
    Node* p1 = m_head->m_next;
    Node* p2 = sp->m_head->m_next;
    while (p1 != m_head  &&  p2 != sp->m_head)
    {
        if (p1->m_value < p2->m_value)
            p1 = p1->m_next;
        else
        {
            if (p1->m_value > p2->m_value)
                insertBefore(p1, p2->m_value);
            else
                p1 = p1->m_next;
            p2 = p2->m_next;
        }
    }
    for ( ; p2 != sp->m_head; p2 = p2->m_next)
        insertBefore(m_head, p2->m_value);
}
Assume that set1, set2, and the old value of *this each have N elements. In terms of the number of linked list nodes visited during the execution of this function, what is its time complexity? Why?

The file sorts.cpp contains an almost complete program that creates a randomly ordered array, sorts it in a few ways, and reports on the elapsed times. Your job is to complete it and experiment with it.

You can run the program as is to get some results for the STL sort algorithm. You won't get any result for insertion sort, because the insertion sort function right now doesn't do anything. That's one thing for you to write.

The objects in the array might not be cheap to copy (it depends on your processor), which might make a sort that does a lot of moving objects around expensive. Your other task will be to create a vector of pointers to the objects, sort the pointers using the same criterion as was used to sort the objects, and then make one pass through the vector to put the objects in the proper order.

Your two tasks are thus:

Implement the insertion_sort function. (Code is on pp. 332-333 in the Carrano book, and also here.)

Implement the compareStudentPtr function and the code in sortUsingPtrs to create and sort the array of pointers.

The places to make modifications are indicated by TODO: comments. You should not have to make modifications anywhere else. (Our solution doesn't.)

When your program is correct, build an optimized version of it to do some timing experiments. On cs32.seas.ucla.edu, build the executable and run it this way:

	g32fast -o sorts sorts.cpp
	./sorts
(You don't have to know this, but this command omits some of the runtime error checking compiler options that our g32 command supplies, and it adds the -O2 compiler option that causes the compiler to spend more time optimizing the machine language translation of your code so that it will run faster when you execute it.)

Under Xcode, select Product / Scheme / Edit Scheme.... In the left panel, select Run, then in the right panel, select the Info tab. In the Build Configuration dropdown, select Release. For Visual C++, it's a little trickier.

Try the program with about 10000 items. Depending on the speed of your processor, this number may be too large or small to get meaningful timings in a reasonable amount of time. Experiment. Once you get insertion sort working, observe the O(N2) behavior by sorting, say, 10000, 20000, and 40000 items.

To further observe the performance behavior of the STL sort algorithm, try sorting, say, 100000, 200000, and 400000 items, or even ten times as many. Since this would make the insertion sort tests take a long time, skip them by setting the TEST_INSERTION_SORT constant at the top of sorts.cpp to false. (Note for Visual C++ users: There's a default limit for the maximum heap size during execution, so you may get strange behavior for a vector of about 350,000 or more of our items (about 566MB). If you like, you can change this in the project's Property Pages, Configuration Properties / Linker / System, Heap Commit Size value.)

Notice that if you run the program more than once, you may not get exactly the same timings each time. This is partly because of not getting the same sequence of random numbers each time, but also because of factors like caching by the operating system.

Turn it in
By Monday, March 6, there will be a link on the class webpage that will enable you to turn in this homework. Turn in one zip file that contains your solutions to the homework problems. The zip file must contain eight files:

oddlist.cpp, a C++ source file with your solution to problem 1a.
oddvector.cpp, a C++ source file with your solution to problem 1b.
badlist.cpp, a C++ source file with your solution to problem 1c.
badvector.cpp, a C++ source file with your solution to problem 1d.
Set.h, a C++ header file with your declaration and implementation of the class and function templates for problem 2.
list.cpp, a C++ source file with the implementation of the two-parameter overload of the listAll function for problem 4a.
sorts.cpp, a C++ source file with your solution to problem 7. Turn in the whole file.
hw.docx, hw.doc, or hw.txt, a Word document or a text file with your solutions to problems 1e, 3, 4b, 5a, 5b, 6a, 6b, and 6c.
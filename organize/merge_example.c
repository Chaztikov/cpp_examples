namespace std {
  OutputIterator merge
     (InputIterator first1, InputIterator last1,
      InputIterator first2, InputIterator last2,
      OutputIterator result [, Compare ]);
}
The example program illustrates a simple merge, the use of a merge with an inserter, and the use of a merge with an output stream iterator.

 void merge_example()
// illustrates the use of the merge algorithm
// see alg7.cpp for complete source code

{
  // make a list and vector of 10 random integers
  std::vector<int> aVec(10);
  std::list<int> aList(10, 0);
  std::generate(aVec.begin(), aVec.end(), randomValue);
  std::sort(aVec.begin(), aVec.end());
  std::generate_n(aList.begin(), 10, randomValue);
  aList.sort();

  // merge into a vector
  std::vector<int> vResult(aVec.size() + aList.size());
  std::merge(aVec.begin(), aVec.end(), 
             aList.begin(), aList.end(), vResult.begin());

  // merge into a list
  std::list<int> lResult;
  std::merge(aVec.begin(), aVec.end(), aList.begin(), 
             aList.end(), inserter(lResult, lResult.begin()));

  // merge into the output
  std::merge(aVec.begin(), aVec.end(), aList.begin(), aList.end(),
             std::ostream_iterator<int,char> (std::cout, " "));
  std::cout << std::endl;
}

// http://stdcxx.apache.org/doc/stdlibug/14-5.html
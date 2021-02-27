//Question:
//
//A permutation is an ordered arrangement of objects. For example, 3124 is one possible permutation 
//of the digits 1, 2, 3 and 4. If all of the permutations are listed numerically or alphabetically, 
//we call it lexicographic order. The lexicographic permutations of 0, 1 and 2 are:
//
//012   021   102   120   201   210
//
//What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
//
//

function listChildNodes(N, path, childNodes)
{
  childNodes.length = 0;

  for (let n = 0; n < N; n++)
  {
    if (path.indexOf(n) < 0)
    {
      childNodes.push(n);
    }
  }
}

//@param N, 0 through N - 1 digits are considered for permutation
//@param max_nthPermutation, stop computation at this no. of permutations
//@param permutationState.path, shared state that accumulates nodes such that if path.length == N,
//       then that accounts for single permutation
//@param permutationState.nthPermutation, if this number is 'k', and the path has N elements, then the elements in path
//       would be kth lexicographic permutation
function permutation(N, max_nthPermutation, permutationState)
{
  const childNodes = [];
  listChildNodes(N, permutationState.path, childNodes);

  if (!childNodes.length)
  {
    ++permutationState.nthPermutation;
  }
  else
  {
    for (let i = 0; i < childNodes.length; i++)
    {
      permutationState.path.push(childNodes[i]);
      permutation(N, max_nthPermutation, permutationState);
      if (permutationState.nthPermutation == max_nthPermutation)
      {
        return;
      }
      permutationState.path.pop();
    }
  }
}

function soln()
{
  const N = 10;
  const max_nthPermutation = 10 ** 6;
  const permutationState = { path: [], nthPermutation: 0 };

  permutation(N, max_nthPermutation, permutationState);

  return permutationState.path;
}

console.log(soln());

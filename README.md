# C++ Double Linked-List (with type params)
### Author: Angel Badillo Hernandez
### Replit: [@It-Is-Legend27](https://replit.com/@It-Is-Legend27)
### Github: [It-Is-Legend27](https://github.com/It-Is-Legend27)
### Website: https://it-is-legend27.repl.co/
# --------------------------------------------
# PLEASE READ:
- Known errors:
  - Using type arguments such as:
    ```c++
    DLList<T> L; // Where T is any non-primitive data type or not printable to standard output.
    L.print(); 
    ```
  - You can, however, print DLList composed of DLList (which must be composed of some primitive data type or "printable" type. *See bullet point above.*)
  ```c++
    DLList<DLList<int>> L;
    L.resize(2);
    L[0].resize(2,1);
    L[1].resize(2,2);
    L.print(); // or cout << L;
    // Output: [[ 1, 1 ], [ 2, 2 ]]
  ```
    

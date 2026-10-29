# Developer guide

For component relationships and application data flow, start with the
[architecture guide](ARCHITECTURE.md).

## Source layout

All C++ sources are in `XMLParser/XMLParser/`.

| Files | Responsibility |
| --- | --- |
| `Main.cpp` | Console dispatch, current document/path, unsaved flag, and command handlers. |
| `XMLElement.h/.cpp` | Element names, attributes, text, child ownership, recursive searches, and serialization. |
| `XMLElementFactory.h/.cpp` | File loading, synthetic document wrapper, recursive parsing, and attribute extraction. |
| `IdList.h/.cpp` | Process-wide counters for supplied and generated ID bases. |
| `ElementFunction.h/.cpp` | Preorder traversal callbacks and path, attribute, and comparison queries. |
| `XPathFactory.h/.cpp` | Conversion of query strings into heap-allocated query objects. |
| `MyString.h/.cpp` | Owning, null-terminated string with copying and moving. |
| `StringView.h/.cpp` | Non-owning character ranges used to parse strings without allocating every slice. |
| `Vector.h` | Contiguous dynamic array with checked indexing. |
| `OrderedMap.h` | Key-sorted array of pairs with binary-search lookup. |
| `Polymorphic_Ptr.h` | Owning pointer that clones on copy and transfers ownership on move. |
| `Predicate.h` | Boolean callback interface for tree searches. |
| `Helpers.h/.cpp` | Numeric conversion and stream-reading helpers. |
| `Polymorphic_Container.h`, `HeterogeneVector.h` | Additional owning polymorphic containers; the element tree directly uses `Vector<ElemPtr>`. |
| `XMLEntry.h` | Empty placeholder, currently unused. |

## Parsing and serialization

`XMLElementFactory::create(const char*)` treats its argument as a **file path**;
the `MyString` and `StringView` overloads treat their arguments as **XML text**.
The file overload returns `nullptr` if opening fails. Parsing errors can throw;
there is no comprehensive validation or cleanup guarantee for partially built
trees.

The stream overload reads from the current stream position, restores that
position through `readAll`, adds the synthetic `root` wrapper, and invokes the
text parser. The text overloads parse one element without adding a wrapper.
Recursive parsing shares a position index: a successful complete parse advances
it past the closing `>` so the caller can find a sibling or its own closing tag.
Attribute parsing assigns IDs through `IdList`.

`XMLElement::save` writes the current element, sorted attributes, stored text,
and descendants. Each child level adds four spaces; `operator<<` starts at zero
indentation. Console print/save handlers skip the synthetic wrapper. Output is
a new serialization, so original layout and attribute order are not retained.

## Ownership and API contracts

- Successful element factories return a raw pointer owned by the caller. Delete
  the returned root once, or transfer it to an `XMLElement::ElemPtr`.
- `ElemPtr` aliases `Polymorphic_Ptr<XMLElement>`. Constructing it from a raw
  pointer takes ownership. Copying invokes `clone()`; moving transfers the
  pointer. Never create two independent owners for the same raw pointer.
- Children are stored in `Vector<ElemPtr>`. `addChild` and `insertChild` clone
  lvalue pointers and transfer rvalue pointers. Raw pointers passed to these
  methods convert to temporary owning pointers. `insertChild` requires an
  existing index (`at < childrenCount()`); use `addChild` to append.
- `childAt`, `getParent`, and `findInTree*` return borrowed pointers. Tree
  searches include the receiver and return the first preorder match or
  `nullptr`; `findChild` searches direct children and returns an index or `-1`.
- Child insertion does not establish a parent link. The `parent` field is also
  an owning, cloning pointer, rather than a back-reference. Do not wrap the
  existing parent address in an `ElemPtr` to set it: that introduces duplicate
  ownership. Ordinary parsed trees leave this field empty.
- Const attribute lookup throws `std::invalid_argument` for a missing key.
  Mutable `OrderedMap::operator[]` inserts a default value on a miss. Changing
  the `id` attribute directly does not consult `IdList`; `removeAttribute`
  explicitly rejects removing it.
- A `StringView` borrows its source buffer. Keep the source alive and do not
  reallocate it while using the view. `substr` and `trim` return views;
  `toString` makes an owning copy. Searches return indices relative to the
  view or `-1`; reverse-search offsets count back from the end.
- `XPathFactory::create` returns a caller-owned query, or `nullptr` for a
  rejected expression. Check the result before dereferencing it. Traversal
  requires a non-null element. Query results accumulate across traversals;
  construct a new query or clear `result()` before reuse.
- Polymorphic pointer/container element types must provide `clone()` and a
  destructor suitable for deletion through `T*`. `Polymorphic_Ptr::reset`
  currently ignores `nullptr`; it is not a way to clear the pointer.

## Extending and checking the project

To add a console command, add its dispatch branch, handler, built-in help text,
and README entry. To add a query, derive from `XPathQuery`, implement the
callback and `clone`, then extend `XPathFactory`. The shared traversal already
visits every element, so each callback can operate on the current node and its
direct children.

The repository has no automated test target. Build with the README command;
the current `OrderedMap` exception-specification mismatch blocks this check.
After that issue is resolved, manually exercise the README example using a
fresh process and a new output filename. Check generated IDs with `print`,
zero-based child access, missing-attribute errors, and the behavior of each
query form. Keep source fixtures unchanged when testing saves. The README lists
existing behavior that can prevent a successful round trip or interactive flow.

# XMLParser

A C++ console application for loading, inspecting, editing, and saving a small
subset of XML. It includes an in-memory element tree, attribute editing, and
three XPath-style query classes. Strings, containers, and polymorphic ownership
are implemented locally rather than supplied by an XML library.

## Build and run

The supplied solution targets **Visual Studio 2022**, the **MSVC v143** C++
toolset, and a **Windows 10 SDK**. Install the Desktop development with C++
workload. No third-party libraries are required.

1. Open [XMLParser/XMLParser.sln](XMLParser/XMLParser.sln).
2. Select `Debug` or `Release` and `x64` or `x86`.
3. Build the solution and run the `XMLParser` console project.

From a Visual Studio Developer PowerShell, the equivalent x64 Debug build is:

```powershell
msbuild .\XMLParser\XMLParser.sln /p:Configuration=Debug /p:Platform=x64
.\XMLParser\x64\Debug\XMLParser.exe
```

**Current build issue:** MSVC reports C2382 in `OrderedMap.h`: the move
constructor and move assignment declarations specify `noexcept`, but their
definitions omit it. Those exception specifications must agree before the
application can be built. The documentation change does not repair this issue.
The code also uses MSVC-specific `std::exception(message)` constructors, so
building with GCC or Clang may require portability changes.

## Using the console

Enter the command name alone at `Enter command:`. Arguments are requested in
subsequent prompts, one response per line. For example, enter `select`, then the
element ID, then the attribute name; entering `select 0 id` as one line is not
supported. Commands and names are case-sensitive. Enter file paths without
surrounding quotes; relative paths use the process working directory.

| Command | Subsequent input, in order | Action |
| --- | --- | --- |
| `open` | File path | Load a file, first invoking `close` for an existing document. |
| `print` | None | Print the loaded document with indentation and generated IDs. |
| `save` | None | Write to the current file and clear the unsaved flag. |
| `save as` | Destination path | Write to another file and make it the current path. |
| `close` | `yes` or `no`, only if edited | Invoke the document close handler; see the limitation below. |
| `help` | None | Print the built-in command list. |
| `select` | Element ID, attribute name | Print an attribute value. |
| `set` | Element ID, attribute name, new value | Add or replace an attribute. |
| `children` | Element ID | List direct child names and attributes. |
| `child` | Element ID, child position | Print a direct child using a **zero-based** index. |
| `text` | Element ID | Print that element's own stored text, excluding descendant text. |
| `delete` | Element ID, attribute key | Request attribute removal; removing `id` is forbidden. |
| `newchild` | Parent element ID, child ID | Append an empty, unnamed child with an allocated ID. |
| `xpath` | Query string | Print the number of results and a list of strings. |
| `exit` | Save response if edited | Leave the loop and invoke the close handler. |

`set`, `delete`, and `newchild` mark the document as edited. `save` and `save as`
overwrite their destination. A caught command exception is reported by `main`
and ends the application; there is no per-command error recovery.

### Example session

After the build issue is resolved, this input sequence uses the bundled
[f.xml](XMLParser/XMLParser/f.xml) from the repository root:

```text
open
XMLParser/XMLParser/f.xml
select
0
id
text
Unnamed
xpath
person/name
set
0
status
active
save as
edited.xml
exit
```

On the first load in a fresh process, `select` prints `0`, `text` prints
`John Smith`, and `person/name` collects `John Smith` and `Ivan Petrov`.
`save as` writes the edited document to `edited.xml` in the working directory.

## XML representation and IDs

The parser expects explicit opening and closing tags and double-quoted
attributes. Use leaf elements for text and parent elements for child nodes.
For example:

```xml
<person id="person1">
    <name>Jane Doe</name>
    <address type="home">Sofia</address>
</person>
```

File and file-stream loading wrap the input in an internal
`<root id="ROOT">...</root>` element, allowing multiple top-level elements such
as those in `f.xml`. `print` and saving serialize only the wrapper's children.
An explicit `<root>` in the input, such as in [f2.xml](XMLParser/XMLParser/f2.xml),
is a separate element inside that wrapper.

Each parsed element receives an `id` attribute. Missing IDs are allocated from
`Unnamed`; repeated base IDs normally gain suffixes such as `Unnamed_1` or
`person1_1`. Allocation state lasts for the entire process, including across
file opens. It does not guarantee uniqueness when an input already contains a
generated suffix, and editing `id` with `set` bypasses the allocator. Use `print`
to inspect the current IDs.

## XPath-style queries

Queries traverse the entire tree in preorder. They return strings, and name
matching is case-sensitive. This is a small custom query language, not a full
XPath implementation.

| Form | Meaning | Current status |
| --- | --- | --- |
| `person/name` | Text of each direct `name` child of every `person`. | Implemented. |
| `address[@type]` | Intended to return `type` attribute values for `address` elements. | The factory retains `@` in the attribute name, so ordinary `type` attributes do not match. |
| `person[name="John Smith"]/address` | Intended to return `address` text for people with a matching `name` child. | The factory retains `/` in the selected child name, preventing ordinary `address` matches. |

Leading `/`, `//`, wildcards, namespaces, positional predicates, and arbitrary
multi-step paths are unsupported. Open a document before querying. Invalid
queries can return a null query pointer which the console does not check.

## Current limitations

- XML declarations, comments, CDATA, DTDs, self-closing tags, and single-quoted
  attributes are unsupported. Closing tag names are not validated. Malformed
  input can throw or access invalid data.
- Mixed text and child content is not preserved. Leaf text is trimmed, with
  an existing `StringView::trim` range bug for leading whitespace that can also
  affect reloading formatted output.
- Entity references are not decoded or escaped. Saving changes whitespace and
  attribute order, adds generated IDs, and always writes explicit closing tags.
- `close` only frees the current document when the unsaved flag is set; an
  unedited or just-saved document remains loaded after `close`.
- `child` and the save confirmation use formatted input, leaving a newline that
  the next line-based prompt can read as an empty command or response.
- Attribute deletion shifts map entries without reducing the stored count.
  `newchild` does not prompt for a tag name or text, so it cannot produce a
  complete named XML element through the console alone.
- ID suffix allocation fails at counter value 10 because of an existing numeric
  conversion boundary error in `Helpers.cpp`.

See [the architecture guide](docs/ARCHITECTURE.md) for component relationships,
document ownership, and the loading, query, and saving flows. The
[developer guide](docs/DEVELOPMENT.md) covers API contracts and validation.

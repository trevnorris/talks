Performance differences working with JS object properties in JS vs CC.

There are 4 tests:

**setInCCSlow**: Creates a new JS object using `Object::New()` v8 API, then
creates a new JS string literal using `String::NewFromUtf8()` for the name of
each property that is being assigned.

The focus of this test is to show the performance hit from creating new JS
objects on every call when, in fact, they could be preserved for latter usage.


**setInCCSym**: Using the v8 API we're able to create a `Persistent`\* symbol of
key values that will be used in the future. This way the same string literal can
be used in future function calls.

Here we can demonstrate the performance advantages by paying attention to simple
tasks. Like taking notice when the same value will be used multiple times.


**setInJS**: The object is created in C++, but then passed to the JS function
`setProperties` where each object property is assigned. Notice in the `Call()`
method we're passing the new object as the first argument. Every C++ to JS call
requires the context be set. It was easier to then set the context to the object
to which we're assigning values than to pass it as a function argument.

As shown here it's much faster to set object properties in JS than C++. So much
so, in fact, even with the round-trip cost of calling to JS from C++ it's still
significantly faster.


**setInJSObj**: The C++ function creates `Local` values for each argument. All
of which are passed to the JS function `setPropObj` where the object is both
created and properties set from JS.

Finally we've hit the peak of performance in this set. By simply calling out to
a JS function which both creates an object and sets the properties we're now
approximately 16x's faster than the first example.


\* **Quick Note**: v8 objects with `Local` only exist as long as the function's
scope. For that reason it's necessary to create a `Persistent` instance that
will exist until the user explicitly removes it using `.Dispose()`.


**Building**: These examples only work on the v0.11 branch of Node. You can
compile these examples yourself using against the master branch roughly by doing
the following:
```
$ /path/to/latest/node $(which node-gyp) rebuild \
  --release \
  --nodedir=/path/to/latest
```

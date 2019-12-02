// For some dependencies, it makes sense to wrap the imported libraries. Easiest way is to have a static library
// reference a single empty source file, link privately to the dependency and then add the necessary include dirs. This
// gives the most control over the interface.
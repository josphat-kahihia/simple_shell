void concatenatePaths(const char *path1, const char *path2, char *result) 
{
    // Copy characters from the first path
    while (*path1 != '\0') {
        *result = *path1;
        result++;
        path1++;
    }

    // Add a path separator if needed
    if (*(result - 1) != '/' && *path2 != '/') {
        *result = '/';
        result++;
    }

    // Copy characters from the second path
    while (*path2 != '\0') {
        *result = *path2;
        result++;
        path2++;
    }

    // Null-terminate the result string
    *result = '\0';
}
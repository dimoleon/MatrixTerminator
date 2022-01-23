# Βιβλιογραφία 

## Για την δυναμική συστοιχία πινάκων η απάντηση του autistic εδώ: 

    https://stackoverflow.com/a/46351960
    > Unfortunately, there are limitations. While you're still learning to use a function, you shouldn't assume the role of a teacher, for example. I often read answers from those who seemingly don't know how to use realloc (i.e. the currently accepted answer!) telling others how to use it incorrectly, occasionally under the guise that they've omitted error handling, even though this is a common pitfall which needs mention. Here's an answer explaining how to use realloc correctly. Take note that the answer is storing the return value into a different variable in order to perform error checking.
    >
    > Introduce a little-known feature which shines for exactly this usecase: flexible array members!
    >
    > When you define your `struct`, declare your array *at the end* of the structure, withour any upper bound. For example: 
    >
    >> `struct int_list {
            size_t size;
            int value[];
        };`


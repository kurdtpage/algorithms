/*
    binary_search(word, start, end)
        1. if list.count == 0, return 0
        2. middle = floor(last-first/2)
        3. if middle == word return middle
        4. if middle > word binary_search(word, start, middle)
        5. if middle < word binary_search(word, middle, end)
 */

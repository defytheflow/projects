

def split(array: list, chunk_size: int) -> list:
    """
        Splits an array in chunks of chunk_size.
        Returns a list of tuple(chunk) size of chunk_size.
    """
    chunks = []
    for i in range(0, len(array), chunk_size):
        temp = []
        for j in range(chunk_size):
            try:
                temp.append(array[i+j])
            except IndexError:
                print("Chunks are not equal")
                break
        chunks.append(tuple(temp))
    return chunks


def show_execution_time(func):
    """ This decorator prints out Execution time of the input function. """
    import time
    def wrapper():
        start = time.time()
        func()
        end = time.time()
        print("Execution time:", end - start)
    return wrapper

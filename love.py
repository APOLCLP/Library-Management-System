filename = "distributed_books.csv"  # Change this to your actual file name

with open(filename, "r", encoding="utf-8") as file:
    for line_num, line in enumerate(file, start=1):
        comma_count = line.count(',')
        if comma_count != 16:
            print(f"Line {line_num} has {comma_count}")

# logic.py

def calculate_scholarship(marks):
    if marks >= 90:
        return 50
    elif marks >= 80:
        return 40
    elif marks >= 70:
        return 30
    else:
        return 0

class Student:
    def __init__(self, name, marks):
        self.name = name
        self.marks = marks
        self.scholarship = calculate_scholarship(marks)

def main():
    try:
        with open("students.txt", "r") as fin:
            lines = [line.strip() for line in fin if line.strip()]
            if not lines:
                print("students.txt is empty.")
                return

            try:
                n = int(lines[0])
            except ValueError:
                print("First line of students.txt must be an integer (student count).")
                return

            if len(lines[1:]) < n:
                print(f"Expected {n} students, but found only {len(lines[1:])}.")
                return

            students = []
            for line in lines[1:n+1]:
                parts = line.split()
                if len(parts) != 2:
                    continue
                name, marks = parts
                students.append(Student(name, int(marks)))

    except FileNotFoundError:
        print("students.txt not found.")
        return

    # Sort by marks descending
    students.sort(key=lambda x: x.marks, reverse=True)

    with open("result.txt", "w") as fout:
        fout.write("🎓 Scholarship Allocation Result\n\n")
        for s in students:
            fout.write(f"Name: {s.name}\n")
            fout.write(f"Marks: {s.marks}%\n")
            fout.write(f"Scholarship Awarded: {s.scholarship}%\n")
            fout.write("-----------------------------\n")

        fout.write("\n🏆 Top 3 Scorers:\n")
        for i, s in enumerate(students[:3]):
            fout.write(f"{i+1}. {s.name} ({s.marks}%)\n")

    print("✅ result.txt generated successfully.")

if __name__ == "__main__":
    main()

let students = [];

document.getElementById("student-form").addEventListener("submit", function (e) {
  e.preventDefault();

  const name = e.target.name.value.trim();
  const marks = parseInt(e.target.marks.value);

  if (!name || isNaN(marks)) {
    alert("Please enter valid name and marks.");
    return;
  }

  students.push({ name, marks });
  e.target.reset();
  updateStudentList();
});

function updateStudentList() {
  if (students.length === 0) {
    document.getElementById("studentListDisplay").innerText = "No students added yet.";
    return;
  }

  let list = "";
  students.forEach((s, i) => {
    list += `${i + 1}. ${s.name} — ${s.marks}%\n`;
  });

  document.getElementById("studentListDisplay").innerText = list;
}

function calculateScholarship(marks) {
  if (marks >= 90) return 50;
  if (marks >= 80) return 40;
  if (marks >= 70) return 30;
  return 0;
}

function showResult() {
  if (students.length === 0) {
    document.getElementById("resultDisplay").innerText = "No students to evaluate.";
    return;
  }

  // Sort by marks descending
  const sorted = [...students].sort((a, b) => b.marks - a.marks);

  let result = "🎓 Scholarship Allocation Result\n\n";

  sorted.forEach((s) => {
    const scholarship = calculateScholarship(s.marks);
    result += `Name: ${s.name}\n`;
    result += `Marks: ${s.marks}%\n`;
    result += `Scholarship Awarded: ${scholarship}%\n`;
    result += "-----------------------------\n";
  });

  result += "\n🏆 Top 3 Scorers:\n";
  sorted.slice(0, 3).forEach((s, i) => {
    result += `${i + 1}. ${s.name} (${s.marks}%)\n`;
  });

  document.getElementById("resultDisplay").innerText = result;
}

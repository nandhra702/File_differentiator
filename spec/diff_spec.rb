require 'open3'

RSpec.describe 'diff' do
  def run_diff(file1_content, file2_content)
    File.write('file1.txt', file1_content)
    File.write('file2.txt', file2_content)
    stdout, stderr, status = Open3.capture3("./diff file1.txt file2.txt")
    File.delete('file1.txt', 'file2.txt')
    stdout
  end

 it 'highlights the difference in red' do
  output = run_diff("apple\nbanana\ncherry\n", "apple\nbanana pie\ncherry\n")

  # Check for red highlighting in the output
  expect(output).to include("\e[31","\e[0m")
end


  it 'ignores differences in extra spaces' do
    output = run_diff("apple banana\n", "   apple banana    \n")
    expect(output).to include("apple banana") # they should be treated as equal
  end

  it 'ignores single-line comments' do
    output = run_diff("apple\n// this is a comment\nbanana\n", "apple\nbanana\n")
    expect(output).not_to include("comment")
  end

  it 'ignores multi-line comments' do
    output = run_diff("apple\n/* multi\nline comment */\nbanana\n",
                      "apple\nbanana\n")
    expect(output).not_to include("multi")
    expect(output).not_to include("line")
  end
end

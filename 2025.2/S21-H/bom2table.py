import csv
from io import StringIO

def convert_csv_to_markdown_table(csv_content):
    """
    Converts a CSV string into a Markdown table string.

    Args:
        csv_content (str): The content of the CSV file as a string.

    Returns:
        str: A string containing the formatted Markdown table.
    """
    # Use StringIO to treat the string content as a file
    csv_file = StringIO(csv_content)
    reader = csv.reader(csv_file)

    # Read all rows into a list
    rows = list(reader)

    # Check if there are any rows to process
    if not rows:
        return ""

    # The first row is the header
    header = rows[0]
    data_rows = rows[1:]

    # Construct the header line for the Markdown table
    # The header is created by joining the column names with '|'
    markdown_header = "| " + " | ".join(header) + " |"

    # Construct the separator line (e.g., |---|---|---|)
    # This line has a dash for each column
    separator = "|-" + "-|-".join(["-"] * len(header)) + "-|"

    # Construct the data rows
    markdown_rows = []
    for row in data_rows:
        # Each row is created by joining the cell values with '|'
        markdown_rows.append("| " + " | ".join(row) + " |")

    # Combine all parts into a single Markdown table string
    markdown_table = "\n".join([markdown_header, separator] + markdown_rows)

    return markdown_table

if __name__ == "__main__":
    # The name of the CSV file to be read
    file_name = "Template.csv"
    # The name of the output Markdown file
    output_file_name = "output.md"

    try:
        # Open and read the content of the specified CSV file
        with open(file_name, 'r', encoding='utf-8') as f:
            csv_data = f.read()

        # Convert the CSV content to a Markdown table
        markdown_output = convert_csv_to_markdown_table(csv_data)

        # Write the Markdown table to the output file
        with open(output_file_name, 'w', encoding='utf-8') as f:
            f.write(markdown_output)

        print(f"Markdown table successfully written to {output_file_name}")

    except FileNotFoundError:
        print(f"Error: The file '{file_name}' was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

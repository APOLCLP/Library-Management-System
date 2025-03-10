import pandas as pd
from datetime import datetime
import os

def get_last_run_date(filename):
    try:
        with open(filename, 'r') as file:
            return datetime.strptime(file.read().strip(), '%Y-%m-%d')
    except FileNotFoundError:
        return None
    except ValueError:
        print(f"Invalid date format in {filename}.")
        return None

def save_last_run_date(filename, date):
    try:
        with open(filename, 'w') as file:
            file.write(date.strftime('%Y-%m-%d'))
    except Exception as e:
        print(f"Failed to save date to {filename}: {e}")

def update_days_borrowed(csv_file, last_run_date_file):
    try:
        # Load the CSV file
        data = pd.read_csv(csv_file)

        # Get the current date
        current_date = datetime.now()

        # Get the last run date
        last_run_date = get_last_run_date(last_run_date_file)

        # If this is the first run, set the last run date to the current date
        if last_run_date is None:
            last_run_date = current_date
            save_last_run_date(last_run_date_file, last_run_date)
            return

        # Calculate the difference between the current date and the last run date
        days_diff = (current_date - last_run_date).days

        # Update the 'DaysBorrowed' columns by adding the days difference
        for col in ['DaysBorrowed1', 'DaysBorrowed2', 'DaysBorrowed3', 'DaysBorrowed4', 'DaysBorrowed5']:
            if col in data.columns:
                data[col] = data[col].apply(lambda x: x + days_diff if pd.notna(x) else x)

        # Save the updated data back to the CSV file
        data.to_csv(csv_file, index=False)

        # Save the current date as the last run date
        save_last_run_date(last_run_date_file, current_date)
    except Exception as e:
        print(f"An error occurred: {e}")

# Specify the CSV file and the last run date file
current_dir = os.path.dirname(os.path.abspath(__file__))
csv_file = os.path.join('../dataset/distributed_books.csv')
last_run_date_file = os.path.join(current_dir, 'last_run_date.txt')

# Run the update function
update_days_borrowed(csv_file, last_run_date_file)

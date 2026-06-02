#!/usr/bin/env python3

"""Calculate how many days until a given date."""

import sys
from datetime import date, datetime


def days_until(target: date) -> int:
    return (target - date.today()).days


def parse_date(s: str) -> date:
    today = date.today()

    # Formats that include a year
    for fmt in ("%Y-%m-%d", "%d/%m/%Y", "%d-%m-%Y", "%Y/%m/%d", "%B %d %Y", "%b %d %Y", "%d %B %Y", "%d %b %Y"):
        try:
            return datetime.strptime(s, fmt).date()
        except ValueError:
            continue

    # Formats without a year — implicitly use the current year
    for fmt in ("%B %d", "%b %d", "%d %B", "%d %b", "%m/%d", "%m-%d"):
        try:
            parsed = datetime.strptime(s, fmt)
            return parsed.replace(year=today.year).date()
        except ValueError:
            continue

    raise ValueError(
        f"Unrecognized date format: {s!r}. "
        "Try YYYY-MM-DD, 'Sep 13', 'September 13', or 'Sep 13 2027'."
    )


def main():
    if len(sys.argv) < 2:
        print(f"Usage: {sys.argv[0]} <date>  (e.g. 2026-12-31, 'Sep 13', 'September 13')")
        sys.exit(1)

    # Join multiple args so bare invocations like: days_until.py Sep 13 work
    arg = " ".join(sys.argv[1:])

    try:
        target = parse_date(arg)
    except ValueError as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)

    delta = days_until(target)

    if delta > 0:
        print(f"{target} is {delta} day{'s' if delta != 1 else ''} from now.")
    elif delta == 0:
        print(f"{target} is today.")
    else:
        print(f"{target} was {-delta} day{'s' if delta != -1 else ''} ago.")


if __name__ == "__main__":
    main()

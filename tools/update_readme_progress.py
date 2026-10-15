#!/usr/bin/env python3
"""Refresh the README's US progress badges from a local objdiff report."""

import argparse
import json
from pathlib import Path
from urllib.parse import quote

START = '<!-- progress:start -->'
END = '<!-- progress:end -->'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('report', type=Path, help='GXXE01 objdiff report.json')
    parser.add_argument('--readme', type=Path, default=Path('README.md'))
    args = parser.parse_args()
    measures = json.loads(args.report.read_text())['measures']
    badges = []
    for label, field in [('US code matched', 'matched_code_percent'),
                         ('US data matched', 'matched_data_percent')]:
        percent = float(measures[field])
        if not 0 <= percent <= 100:
            raise ValueError(f'{field} must be between 0 and 100')
        url = 'https://img.shields.io/static/v1?' + '&'.join([
            'label=' + quote(label), 'message=' + quote(f'{percent:.2f}%'),
            'color=blue',
        ])
        badges.append(f'![{label}: {percent:.2f}%]({url})')
    text = args.readme.read_text()
    if text.count(START) != 1 or text.count(END) != 1:
        raise ValueError('README must contain exactly one progress marker pair')
    before, rest = text.split(START)
    _, after = rest.split(END)
    args.readme.write_text(before + START + '\n' + ' '.join(badges) + '\n' + END + after)


if __name__ == '__main__':
    main()

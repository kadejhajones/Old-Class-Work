#!/usr/bin/env python3
# Shane McDonough

import matplotlib.pyplot as plt
import json
import glob
from typing import Callable

def value_and_percent(total: int) -> Callable[[float], str]:
	return lambda x: f'{x:.3}%\n({round(x * total / 100)})'

def add_labels(vals, offset=0):
	# https://www.geeksforgeeks.org/adding-value-labels-on-a-matplotlib-bar-chart/#
	for i, val in enumerate(vals):
		plt.text(i + offset, val, val)

def print_json(data: dict):
	print(json.dumps(data, indent=4))

def inc_dict(d: dict[any, int], key: any):
	if key in d:
		d[key] += 1
	else:
		d[key] = 1

def read_objs():
	'''Read all of the har datafiles'''
	objects = []
	for filename in glob.glob('harhar/*'):
		with open(filename, 'r') as file:
			print(f'reading file "{filename}"')
			objects.append(json.load(file)['log'])
	return objects

def creators_pie(objs: list[dict]):
	'''Display a pie chart of the creators used'''
	PIE_RADIUS = 1.3
	creators = dict()
	total = 0
	for obj in objs:
		name = obj['creator']['name']
		version = obj['creator']['version']
		if name in creators:
			inc_dict(creators[name], version)
		else:
			creators[name] = { version: 1 }
		total += 1
	autopct = value_and_percent(total)
	plt.subplot(2, 1, 1)
	plt.pie(
		[ sum(creator.values()) for creator in creators.values() ],
		labels=creators.keys(),
		radius=PIE_RADIUS,
		autopct=autopct
	)
	plt.title('Creator used')
	print_json(creators)
	creator_counts = dict()
	for name, obj in creators.items():
		for version, count in obj.items():
			full_name = f'{name} v{version}'
			creator_counts[full_name] = count
	print_json(creator_counts)
	plt.subplot(2, 1, 2)
	plt.pie(
		creator_counts.values(),
		labels=creator_counts.keys(),
		radius=PIE_RADIUS,
		# https://stackoverflow.com/questions/59644751/matplotlib-pie-chart-show-both-value-and-percentage
		autopct=autopct
	)
	plt.title('Creator used with versions')

def entries_bar(objs: list[dict]):
	entries_count = dict()
	for obj in objs:
		for entry in obj['entries']:
			inc_dict(entries_count, entry['request']['method'])
	print_json(entries_count)
	x = entries_count.keys()
	y = entries_count.values()
	plt.bar(x, y)
	add_labels(y)
	plt.title('Entry Method Type by Count')
	plt.xlabel('Methods')
	plt.ylabel('Count')

def entry_priorty(objs: list[dict]):
	entries_count = dict()
	for obj in objs:
		for entry in obj['entries']:
			inc_dict(entries_count, (entry.get('_priority') or 'none').lower())
	print(entries_count)
	print_json(entries_count)
	x = entries_count.keys()
	print(x)
	y = entries_count.values()
	plt.bar(x, y)
	add_labels(y)
	plt.title('Entry Priority Type by Count')
	plt.xlabel('Priority')
	plt.ylabel('Count')

def entry_resource_type(objs: list[dict]):
	entries_count = dict()
	for obj in objs:
		for entry in obj['entries']:
			inc_dict(entries_count, (entry.get('_resourceType') or 'none').lower())
	print(entries_count)
	print_json(entries_count)
	x = entries_count.keys()
	print(x)
	y = entries_count.values()
	plt.bar(x, y)
	add_labels(y, -0.5)
	plt.title('Entry Resource Type by Count')
	plt.xlabel('Resource Type')
	plt.ylabel('Count')
	plt.xticks(rotation=45)

def entry_time(objs: list[dict]):
	times = [
		entry['time']
		for obj in objs
		for entry in obj['entries']
	]
	bins = len(times) // 75
	plt.subplot(2, 1, 1)
	plt.hist(times, bins = bins,range=(0, 500))
	plt.title('Time Elapsed in request by Count')
	plt.xlabel('Time Elapsed in request')
	plt.ylabel('Count')
	plt.subplot(2, 1, 2)
	plt.hist(times, bins = bins)
	plt.xlabel('Time Elapsed in request')
	plt.ylabel('Count')
	# plt.xticks(rotation=45)

def main():
	'''Driver Code'''
	objects = read_objs()
	creators_pie(objects)
	# plt.figure()
	# entries_bar(objects)
	# plt.figure()
	# entry_priorty(objects)
	plt.figure()
	entry_resource_type(objects)
	plt.figure()
	entry_time(objects)
	plt.show()

if __name__ == '__main__':
	main()

from pathlib import Path
import numpy

from check_on_results.check_general import check_interface
from check_decorators.print_name import printNameDecorator
from utils.find_reference import find_reference_folder
from utils.find_output import find_dated_output_folder

@printNameDecorator
class integrity_compare(check_interface):
    def __init__(self, study_path):
        super().__init__(study_path)
        self.ref_folder = find_reference_folder(self.study_path)

    def run(self):
        self.compare_files()

    def name(self):
        return "integrity compare"

    def compare_files(self):
        reference_values = get_integrity_check_values(self.ref_folder)
        print(
            "************************************* reference_values = {} *************************************".format(
                reference_values))
        path_to_output = find_dated_output_folder(self.study_path)
        output_values = get_integrity_check_values(path_to_output)
        print("************************************* output_values = {} *************************************".format(
            output_values))
        numpy.testing.assert_allclose(reference_values[0:8], output_values[0:8], rtol=1e-3, atol=0)


def get_integrity_check_values(output: Path) -> numpy.ndarray:

    integrity_path = find_integrity_path(output)
    with open(integrity_path, 'r') as integrity_file:
        output_values = [float(x) for x in integrity_file]
    assert len(output_values) == 8
    return numpy.array(output_values)

def find_integrity_path(output_dir):
    files_found = []
    for path in Path(output_dir).rglob('checkIntegrity.txt'):
        files_found.append(path)
    assert len(files_found) == 1
    return files_found[0]
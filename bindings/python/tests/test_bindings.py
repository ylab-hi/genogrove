import unittest
import pygenogrove

class TestGrove(unittest.TestCase):
    def setUp(self):
        self.grove = pygenogrove.Grove(3)

        def test_insert(self):
            interval = pygenogrove.Insert("chr1", 1000, 2000)
            self.grove.insert(interval)
            self.assertEqual(len(self.grove), 1)

        def test_search(self):
            self.grove.insert(pygenogrove.Interval("chr1", 1000, 2000))
            result = self.grove.search(pygenogrove.Interval("chr1", 1500, 1600))
            self.assertTrue(len(results) > 0)

if __name__ == "__main__":
    unittest.main()


"""
thermonuclear NDI records and subrecords
"""
from __future__ import annotations
__all__: list[str] = ['InterpolationRegions', 'Temperatures']
class InterpolationRegions:
    """
    A subrecord for representing interpolate data regions
    """
    def __init__(self, endIndices: list[int], interpTypes: list[int]) -> None:
        """
        Initialise the subrecord
        
        Arguments:
            self           the subrecord
            endIndices     1-based indices signifying the inclusive end of each region's data    interpTypes    integers specifying the interpolation type for each region
        """
    def to_string(self) -> str:
        """
        Return the string representation of the subrecord
        
        Arguments:
            self    the subrecord
        """
    @property
    def boundaries(self) -> ...:
        """
        Return the 1-based indices for the end of each region
        """
    @property
    def empty(self) -> bool:
        """
        Flag indicating whether or not the subrecord is empty
        """
    @property
    def interpolants(self) -> ...:
        """
        Return the interpolation types
        """
    @property
    def number_interpolation_regions(self) -> int:
        """
        Return the number of interpolation regions
        """
    @property
    def size(self) -> int:
        """
        The size of the subrecord
        """
    @property
    def values(self) -> ...:
        """
        The data values of the subrecord
        """
class Temperatures:
    """
    A temperature record for thermonuclear data
    """
    @staticmethod
    def from_string(string: str, number: int) -> Temperatures:
        """
        Read the record from a string
        
        An exception is raised if something goes wrong while reading the
        record
        
        Arguments:
            string    the string representing the record
            number    the number of kerma values to be read
        """
    def __init__(self, values: list[float]) -> None:
        """
        Initialise the record
        
        Arguments:
            self      the record
            values    the temperature values
        """
    def to_string(self) -> str:
        """
        Return the string representation of the record
        
        Arguments:
            self    the record
        """
    @property
    def empty(self) -> bool:
        """
        Flag indicating whether or not the record is empty
        """
    @property
    def keyword(self) -> str:
        """
        The record keyword
        """
    @property
    def number_temperatures(self) -> int:
        """
        The number of temperatures defined by this record
        """
    @property
    def size(self) -> int:
        """
        The size of the record
        """
    @property
    def values(self) -> ...:
        """
        The data values of the record
        """

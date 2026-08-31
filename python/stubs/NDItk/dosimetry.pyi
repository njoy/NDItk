"""
Dosimetry NDI records and subrecords
"""
from __future__ import annotations
import typing
__all__: list[str] = ['Metadata']
class Metadata:
    """
    A group Metadata record for dosimetry data
    """
    def __init__(self, zaid: str, libname: str, process: str, awr: float, temperature: float, dilution: float, groups: int, reactions: int, information: str | None = None, source: str | None = None, weight: float | None = None, upscatter: int | None = None, downscatter: int | None = None) -> None:
        """
        Initialise the record
        
        Arguments:
            self                the metadata
            zaid                the zaid of the table
            libname             the library name
            process             the processing date
            awr                 the atomic weight ratio of the target (with respect
                                to the neutron mass)
            temperature         the temperature of the target
            dilution            the dilution (aka sigma0)
            groups              the number of groups in the primary group structure
            reactions           the number of reactions defined in the table
            information         the table information line (optional)
            source              the source date (optional)
            weight              the atomic weight of the target (optional)
            upscatter           the number of upscatter groups (optional)
            downscatter         the number of downscatter groups (optional)
        """
    def to_string(self) -> str:
        """
        Return the string representation of the subrecord
        
        Arguments:
            self    the metadata
        """
    @property
    def atomic_weight(self) -> float | None:
        """
        The atomic weight of the target
        """
    @property
    def atomic_weight_ratio(self) -> float | None:
        """
        The atomic weight ratio of the target (with respect to the neutron mass)
        """
    @property
    def dilution(self) -> float | None:
        """
        The dilution (aka sigma0)
        """
    @property
    def information(self) -> str | None:
        """
        The table information line
        """
    @property
    def library_name(self) -> str | None:
        """
        The library name
        """
    @property
    def number_downscatter_groups(self) -> int | None:
        """
        The number of downscatter groups defined by this record
        """
    @property
    def number_groups(self) -> int | None:
        """
        The number of groups defined by this record
        """
    @property
    def number_reactions(self) -> int | None:
        """
        The number of reactions defined by this record
        """
    @property
    def number_upscatter_groups(self) -> int | None:
        """
        The number of upscatter groups defined by this record
        """
    @property
    def processing_date(self) -> str | None:
        """
        The process date
        """
    @property
    def source_date(self) -> str | None:
        """
        The source date
        """
    @property
    def temperature(self) -> float | None:
        """
        The temperature of the target
        """
    @property
    def zaid(self) -> str | None:
        """
        The zaid of the table
        """

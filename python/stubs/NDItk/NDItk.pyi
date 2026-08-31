from __future__ import annotations
import typing
from . import depletion
from . import dosimetry
from . import multigroup
from . import sequence
from . import thermonuclear
__all__: list[str] = ['DepletionLibrary', 'DepletionTable', 'DosimetryLibrary', 'DosimetryTable', 'MultigroupLibrary', 'MultigroupTable', 'depletion', 'dosimetry', 'multigroup', 'sequence', 'thermonuclear']
class DepletionLibrary:
    """
    A library containing depletion tables
    """
    @staticmethod
    def from_file(arg0: str) -> DepletionLibrary:
        """
        Read an NDI library from a file
        
        An exception is raised if something goes wrong while reading the
        library
        
        Arguments:
            filename    the file name and path
        """
    def __init__(self, header: str, tables: list[DepletionTable]) -> None:
        """
        Initialise the library
        
        Arguments:
            self               the library
            header             the string header of the library
            tables             a vector of DepletionTable
        """
    @typing.overload
    def get_table(self, index: int) -> DepletionTable:
        """
        Return the table in the library with the associated zaid
        
        Arguments:
            self       the library
            index      the 0-based index of the table in the library file
        """
    @typing.overload
    def get_table(self, zaid: str) -> DepletionTable:
        """
        Return the table in the library with the associated zaid
        
        Arguments:
            self       the library
            zaid       the zaid string of the table in the library file
        """
    def has_table(self, zaid: str) -> bool:
        """
        Check if there is a table in the library with the associated zaid
        
        Arguments:
            self       the library
            zaid       the zaid string of the table in the library file
        """
    def to_file(self, arg0: str) -> None:
        """
        Write an NDI library to a file
        
        Arguments:
            self        the library
            filename    the file name and path
        """
    @property
    def header(self) -> str:
        """
        Return the header in the library
        """
    @property
    def number_tables(self) -> int:
        """
        Return the number of data tables in the library
        """
    @property
    def tables(self) -> list[DepletionTable]:
        """
        Return a vector of tables in the library
        """
class DepletionTable:
    """
    A production/depletion table
    """
    @staticmethod
    def from_file(arg0: str) -> DepletionTable:
        """
        Read an NDI table from a file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    def __init__(self, zaid: str, libname: str, process: str, incident: list[depletion.IncidentParticle], information: str | None = None, source: str | None = None) -> None:
        """
        Initialise the table
        
        Arguments:
            self               the table
            zaid               the zaid of the table
            libname            the library name
            process            the processing date
            incident           a vector of IncidentParticle records
            information        the table information line (optional)
            source             the source date (optional)
        """
    def incident_particle(self, particle: int) -> depletion.IncidentParticle:
        """
        Return the record for an incident particle
        
        Arguments:
            self       the table
            particle   the incident particle identifier to find
        """
    @property
    def incident_particles(self) -> list[depletion.IncidentParticle]:
        """
        Return the vector containing all incident particle records
        """
    @property
    def metadata(self) -> depletion.Metadata:
        """
        Return the metadata of the table
        """
    @property
    def number_incident_particles(self) -> int:
        """
        Return the number of incident particles
        """
class DosimetryLibrary:
    """
    A library containing dosimetry tables
    """
    @staticmethod
    def from_file(arg0: str) -> DosimetryLibrary:
        """
        Read an NDI library from a file
        
        An exception is raised if something goes wrong while reading the
        library
        
        Arguments:
            filename    the file name and path
        """
    def __init__(self, header: str, tables: list[DosimetryTable]) -> None:
        """
        Initialise the library
        
        Arguments:
            self               the library
            header             the string header of the library
            tables             a vector of DosimetryTable
        """
    @typing.overload
    def get_table(self, index: int) -> DosimetryTable:
        """
        Return the table in the library with the associated zaid
        
        Arguments:
            self       the library
            index      the 0-based index of the table in the library file
        """
    @typing.overload
    def get_table(self, zaid: str) -> DosimetryTable:
        """
        Return the table in the library with the associated zaid
        
        Arguments:
            self       the library
            zaid       the zaid string of the table in the library file
        """
    def has_table(self, zaid: str) -> bool:
        """
        Check if there is a table in the library with the associated zaid
        
        Arguments:
            self       the library
            zaid       the zaid string of the table in the library file
        """
    def to_file(self, arg0: str) -> None:
        """
        Write an NDI library to a file
        
        Arguments:
            self        the library
            filename    the file name and path
        """
    @property
    def header(self) -> str:
        """
        Return the header in the library
        """
    @property
    def number_tables(self) -> int:
        """
        Return the number of data tables in the library
        """
    @property
    def tables(self) -> list[DosimetryTable]:
        """
        Return a vector of tables in the library
        """
class DosimetryTable:
    """
    A dosimetry data table
    """
    @staticmethod
    def from_file(arg0: str) -> DosimetryTable:
        """
        Read an NDI table from a file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    def __init__(self, zaid: str, libname: str, process: str, awr: float, temperature: float, dilution: float, structure: multigroup.EnergyGroupStructure, flux: multigroup.FluxWeights, total_xs: multigroup.TotalCrossSection, reaction_xs: multigroup.ReactionCrossSections, information: str | None = None, source: str | None = None, weight: float | None = None) -> None:
        """
        Initialise the table
        
        Arguments:
            self               the table
            zaid               the zaid of the table
            libname            the library name
            process            the processing date
            awr                the atomic weight ratio of the target (with respect
                               to the neutron mass)
            temperature        the temperature of the target
            dilution           the dilution (aka sigma0)
            structure          the primary group structure
            flux               the flux weights
            total_xs           the total cross section
            reaction_xs        the reaction cross section data
            information        the table information line (optional)
            source             the source date (optional)
            weight             the atomic weight of the target (optional)
        """
    def reaction_product_multiplicities(self, type: multigroup.ReactionMultiplicityType) -> multigroup.ReactionMultiplicities:
        """
        The reaction product multipliciies record for the requested multiplicity typeArguments:
            self    the table
            type    the multiplicity type
        """
    @property
    def flux_weights(self) -> multigroup.FluxWeights:
        """
        The flux weight record
        """
    @property
    def metadata(self) -> dosimetry.Metadata:
        """
        The metadata of the table
        """
    @property
    def primary_group_boundaries(self) -> multigroup.EnergyGroupStructure:
        """
        The primary group structure record
        """
    @property
    def reaction_cross_sections(self) -> multigroup.ReactionCrossSections:
        """
        The reaction cross section record
        """
    @property
    def total_cross_section(self) -> multigroup.TotalCrossSection:
        """
        The total cross section record
        """
class MultigroupLibrary:
    """
    A library containing multigroup tables
    """
    @staticmethod
    def from_file(arg0: str) -> MultigroupLibrary:
        """
        Read an NDI library from a file
        
        An exception is raised if something goes wrong while reading the
        library
        
        Arguments:
            filename    the file name and path
        """
    def __init__(self, header: str, tables: list[MultigroupTable]) -> None:
        """
        Initialise the library
        
        Arguments:
            self               the library
            header             the string header of the library
            tables             a vector of MultigroupTable
        """
    @typing.overload
    def get_table(self, index: int) -> MultigroupTable:
        """
        Return the table in the library with the associated zaid
        
        Arguments:
            self       the library
            index      the 0-based index of the table in the library file
        """
    @typing.overload
    def get_table(self, zaid: str) -> MultigroupTable:
        """
        Return the table in the library with the associated zaid
        
        Arguments:
            self       the library
            zaid       the zaid string of the table in the library file
        """
    def has_table(self, zaid: str) -> bool:
        """
        Check if there is a table in the library with the associated zaid
        
        Arguments:
            self       the library
            zaid       the zaid string of the table in the library file
        """
    def to_file(self, arg0: str) -> None:
        """
        Write an NDI library to a file
        
        Arguments:
            self        the library
            filename    the file name and path
        """
    @property
    def header(self) -> str:
        """
        Return the header in the library
        """
    @property
    def number_tables(self) -> int:
        """
        Return the number of data tables in the library
        """
    @property
    def tables(self) -> list[MultigroupTable]:
        """
        Return a vector of tables in the library
        """
class MultigroupTable:
    """
    A multigroup neutron and photon table
    """
    @staticmethod
    def from_file(arg0: str) -> MultigroupTable:
        """
        Read an NDI table from a file
        
        An exception is raised if something goes wrong while reading the
        table
        
        Arguments:
            filename    the file name and path
        """
    def __init__(self, zaid: str, libname: str, process: str, awr: float, temperature: float, dilution: float, structure: multigroup.EnergyGroupStructure, outgoing: list[multigroup.EnergyGroupStructure], velocities: multigroup.Velocities, flux: multigroup.FluxWeights, total_xs: multigroup.TotalCrossSection, reaction_xs: multigroup.ReactionCrossSections, scattering: multigroup.ScatteringMatrix, information: str | None = None, source: str | None = None, weight: float | None = None, fission_q: multigroup.AverageFissionEnergyRelease | None = None, types: multigroup.OutgoingParticleTypes | None = None, transport: multigroup.OutgoingParticleTransportData | None = None, production: list[multigroup.ScatteringMatrix] = [], primary_heating: multigroup.HeatingNumbers | None = None, outgoing_heating: list[multigroup.HeatingNumbers] = [], primary_kerma: multigroup.Kerma | None = None, outgoing_kerma: list[multigroup.Kerma] = []) -> None:
        """
        Initialise the table
        
        Arguments:
            self               the table
            zaid               the zaid of the table
            libname            the library name
            process            the processing date
            awr                the atomic weight ratio of the target (with respect
                               to the neutron mass)
            temperature        the temperature of the target
            dilution           the dilution (aka sigma0)
            structure          the primary group structure
            outgoing           the outgoing particle group structures
            velocities         the velocities
            flux               the flux weights
            total_xs           the total cross section
            reaction_xs        the reaction cross section data
            scattering         the scattering matrix
            information        the table information line (optional)
            source             the source date (optional)
            weight             the atomic weight of the target (optional)
            fission_q          the average fission energy release data (optional)
            types              the outgoing particle types (optional)
            transport          the outgoing particle transport data (optional)
            primary_heating    the primary heating numbers (optional)
            outgoing_heating   the outgoing particle heating numbers (optional)
            primary_kerma      the primary kerma (optional)
            outgoing_kerma     the outgoing particle kermas (optional)
        """
    def fission_neutron_multiplicity(self, type: multigroup.FissionType) -> multigroup.FissionNeutronMultiplicity:
        """
        The fission neutron multiplicity record for the requested fission typeArguments:
            self    the table
            type    the fission type
        """
    def fission_neutron_production(self, type: multigroup.FissionType) -> multigroup.FissionNeutronProduction:
        """
        The fission neutron production record for the requested fission typeArguments:
            self    the table
            type    the fission type
        """
    def fission_neutron_spectrum_matrix(self, type: multigroup.FissionType) -> multigroup.FissionNeutronSpectrumMatrix:
        """
        The fission neutron spectrum matrix record for the requested fission typeArguments:
            self    the table
            type    the fission type
        """
    def fission_neutron_spectrum_vector(self, type: multigroup.FissionType) -> multigroup.FissionNeutronSpectrumVector:
        """
        The fission neutron spectrum vector record for the requested fission typeArguments:
            self    the table
            type    the fission type
        """
    def outgoing_group_boundaries(self, particle: int) -> multigroup.EnergyGroupStructure:
        """
        The group structure record for an outgoing particle
        
        Arguments:
            self       the table
            particle   the outgoing particle identifier
        """
    def outgoing_heating_numbers(self, particle: int) -> multigroup.HeatingNumbers:
        """
        The heating numbers record for an outgoing particle
        
        Arguments:
            self       the table
            particle   the outgoing particle identifier
        """
    def outgoing_kerma(self, particle: int) -> multigroup.Kerma:
        """
        The kerma record for an outgoing particle
        
        Arguments:
            self       the table
            particle   the outgoing particle identifier
        """
    def outgoing_production_matrix(self, particle: int) -> multigroup.ScatteringMatrix:
        """
        The production record for an outgoing particle
        
        Arguments:
            self       the table
            particle   the outgoing particle identifier
        """
    def reaction_product_multiplicities(self, type: multigroup.ReactionMultiplicityType) -> multigroup.ReactionMultiplicities:
        """
        The reaction product multipliciies record for the requested multiplicity typeArguments:
            self    the table
            type    the multiplicity type
        """
    @property
    def average_fission_energy_release(self) -> multigroup.AverageFissionEnergyRelease:
        """
        The average fission energy release record
        """
    @property
    def flux_weights(self) -> multigroup.FluxWeights:
        """
        The flux weight record
        """
    @property
    def metadata(self) -> multigroup.Metadata:
        """
        The metadata of the table
        """
    @property
    def outgoing_particle_transport_data(self) -> multigroup.OutgoingParticleTransportData:
        """
        The outgoing particle transport data record
        """
    @property
    def outgoing_particle_types(self) -> multigroup.OutgoingParticleTypes:
        """
        The outgoing particle types record
        """
    @property
    def primary_group_boundaries(self) -> multigroup.EnergyGroupStructure:
        """
        The primary group structure record
        """
    @property
    def primary_heating_numbers(self) -> multigroup.HeatingNumbers:
        """
        The primary heating numbers record
        """
    @property
    def primary_kerma(self) -> multigroup.Kerma:
        """
        The primary kerma record
        """
    @property
    def reaction_cross_sections(self) -> multigroup.ReactionCrossSections:
        """
        The reaction cross section record
        """
    @property
    def scattering_matrix(self) -> multigroup.ScatteringMatrix:
        """
        The scattering matrix record
        """
    @property
    def total_cross_section(self) -> multigroup.TotalCrossSection:
        """
        The total cross section record
        """
    @property
    def velocities(self) -> multigroup.Velocities:
        """
        The velocity record
        """

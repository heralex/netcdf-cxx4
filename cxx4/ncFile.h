#include <string>
#include "ncGroup.h"
#include "netcdf.h"

#include "netcdf_par.h"


#ifndef NcFileClass
#define NcFileClass


//!  C++ API for netCDF4.
namespace netCDF
{

  /*!
    Class represents a netCDF root group.
    The Ncfile class is the same as the NcGroup class with the additional functionality for opening
    and closing files.
   */
  class NcFile : public NcGroup
   {
   public:

      enum FileMode
     {
        read,	//!< File exists, open read-only.
        write,      //!< File exists, open for writing.
        replace,	//!< Create new file, even if already exists.
        newFile	//!< Create new file, fail if already exists.
     };

      enum FileFormat
         {
        classic,    //!< Classic format, classic data model
        classic64,  //!< 64-bit offset format, classic data model
        nc4,        //!< (default) netCDF-4/HDF5 format, enhanced data model
        nc4classic  //!< netCDF-4/HDF5 format, classic data model
         };


      /*! Constructor generates a \ref isNull "null object". */
      NcFile();

      /*!
        Opens a netCDF file.
        \param filePath    Name of netCDF optional path.
        \aram ncFileFlags File flags from netcdf.h
      */

      NcFile(const std::string& filePath, int ncFileFlags);


      /*!
    Opens a netCDF file.
    \param filePath    Name of netCDF optional path.
    \param fMode       The file mode:
                        - 'read'    File exists, open for read-only.
                        - 'write'   File exists, open for writing.
                        - 'replace' Create new file, even it already exists.
                        - 'newFile' Create new file, fail it exists already.
      */
      NcFile(const std::string& filePath, FileMode fMode);


      /*!
        Opens/creates a netCDF file for parallel I/O.
        Signature based on TE Hilinski's modifications to Lynton Appels code:
             Thomas E. Hilinski <tom.hilinski@colostate.edu>
             Natural Resource Ecology Laboratory, Colorado State University
             IRC <www.nrel.colostate.edu/projects/irc/>
             Date:  2013Jan
        Contributed by Alexander Herzig, 2022-01, Manaaki Whenua - Landcare Research NZ
        \param mpiComm
        \param mpiInfo
        \param fileName
        \param fileMode
      */
      NcFile(MPI_Comm& comm, MPI_Info& info, const std::string fileName, const FileMode fMode);


      /*!
        Create a netCDF file.
        \param filePath    Name of netCDF optional path.
        \param ncFileFlags File flags from netcdf.h
      */
      void create(const std::string& filePath, int ncFileFlags);

      /*!
       * \brief Creates a netCDF file for parallel I/O
       *        Contributed by Alexander Herzig, 2022-01, Manaaki Whenua - Landcare Research NZ
       * \param comm
       * \param info
       * \param filePath
       * \param fMode
       */
      void create(MPI_Comm& comm, MPI_Info& info, const std::string& fileName, int ncFileFlags);

      /*!
        Opens a netCDF file.
        \param filePath    Name of netCDF optional path.
        \param ncFileFlags File flags from netcdf.h
      */
      void open(const std::string& filePath, int ncFileFlags);


      /*!
        Opens a netCDF file.
        \param filePath    Name of netCDF optional path.
        \param fMode       The file mode:
        - 'read'    File exists, open for read-only.
        - 'write'   File exists, open for writing.
        - 'replace' Create new file, even it already exists.
        - 'newFile' Create new file, fail it exists already.
      */
      void open(const std::string& filePath, FileMode fMode);

      /*!
    Creates a netCDF file of a specified format.
    \param filePath    Name of netCDF optional path.
    \param fMode       The file mode:
                        - 'replace' Create new file, even it already exists.
                        - 'newFile' Create new file, fail it exists already.
      */
      NcFile(const std::string& filePath, FileMode fMode, FileFormat fFormat);
      /*!
      Creates a netCDF file of a specified format.
      \param filePath    Name of netCDF optional path.
      \param fMode       The file mode:
                          - 'replace' Create new file, even it already exists.
                          - 'newFile' Create new file, fail it exists already.
      */
      void open(const std::string& filePath, FileMode fMode, FileFormat fFormat);


      /*!
       * \brief Opens a netCDF file for parallel I/O. The file format of the underlying
       *        file is determined automatically.
       *        Contributed by Alexander Herzig, 2022-01, Manaaki Whenua - Landcare Research NZ
       * \param mpiComm   MPI communicator of the processes opening this file in parallel
       * \param mpiInfo   I/O hints  or MPI_INFO_NULL
       * \param fileName  path to the file
       * \param fileMode  NcFile::read | NcFile::write
       */

      void open(MPI_Comm& comm, MPI_Info& info, const std::string fileName, const FileMode fMode);

      //! Close a file before destructor call
      void close();

      /*! destructor */
      virtual ~NcFile(); //closes file and releases all resources

      //! Synchronize an open netcdf dataset to disk
      void sync();

      //! Elect a fill parameter different that the one currently being used
      void set_Fill(int fillmode, int *old_modep);

      //! Redefine variable
      void redef();

      //! Leave define mode, used for classic model
      void enddef();


   private:
       /* Do not allow definition of NcFile involving copying any NcFile or NcGroup.
          Because the destructor closes the file and releases al resources such
          an action could leave NcFile objects in an invalid state */
       NcFile& operator =(const NcGroup & rhs);
       NcFile& operator =(const NcFile & rhs);
       NcFile(const NcGroup& rhs);
       NcFile(const NcFile& rhs);
   };

}


#endif

#ifndef BMI_INCLUDED
#define BMI_INCLUDED

#include <string>

namespace BMI {

typedef enum
{
  CMI_STATUS_CREATED,
  CMI_STATUS_INITIALIZING,
  CMI_STATUS_INITIALIZED,
  CMI_STATUS_UPDATING,
  CMI_STATUS_UPDATED,
  CMI_STATUS_FINALIZING,
  CMI_STATUS_FINALIZED
}
CMI_Component_status;

typedef enum
{
  GRID_TYPE_UNKNOWN = -1,
  GRID_TYPE_UNIFORM,
  GRID_TYPE_RECTILINEAR,
  GRID_TYPE_STRUCTURED,
  GRID_TYPE_UNSTRUCTURED
}
Grid_type;

class Model
{
  public:
    void initialize (std::string);
    void update ();
    void update_until (double);
    void finalize ();
    void run_model ();

    std::string get_component_name ();
    const char **get_input_var_names ();
    const char **get_output_var_names ();

    std::string get_var_type (std::string);
    std::string get_var_units (std::string);
    int get_var_rank (std::string);

    double get_current_time ();
    double get_start_time ();
    double get_end_time ();
    std::string get_time_units ();

    // Assumes arrays start at 0, and have contiguous elements (unit stride).
    double *get_double (std::string, int &);
    double *get_double_at_indices (std::string, int &, int * indices);
    void set_double (std::string, double *);
    double *set_double_at_indices (std::string, int &, int * indices, double * array);

    Grid_type get_grid_type (std::string long_var_name);

    int * get_grid_shape (std::string, int &);
    double * get_grid_spacing (std::string, int &);
    double * get_grid_origin (std::string, int &);

    double * get_grid_x (std::string, int&);
    double * get_grid_y (std::string, int&);
    double * get_grid_z (std::string, int&);

    int * get_grid_connectivity (std::string, int &);
    int * get_grid_offset (std::string, int &);

  private:
    double dt;
    double t;

    int n_x;
    int n_y;

    double dx;
    double dy;
    double **z;

    double **temp_z;
};

};

#endif

#include <stdio.h>
#include <math.h>

/******************************************************************************
 * This program takes an initial estimate of m and c and finds the associated 
 * rms error. It is then as a base to generate and evaluate 8 new estimates, 
 * which are steps in different directions in m-c space. The best estimate is 
 * then used as the base for another iteration of "generate and evaluate". This 
 * continues until none of the new estimates are better than the base. This is
 * a gradient search for a minimum in mc-space.
 * 
 * To compile:
 *   cc -o lr_coursework lr_coursework.c -lm
 * 
 * To run:
 *   ./lr_coursework
 * 
 * Dr Kevan Buckley, University of Wolverhampton, 2018
 *****************************************************************************/

typedef struct point_t {
  double x;
  double y;
} point_t;

int n_data = 1000;
point_t data[];

double residual_error(double x, double y, double m, double c) {
  double e = (m * x) + c - y;
  return e * e;
}

double rms_error(double m, double c) {
  int i;
  double mean;
  double error_sum = 0;
  
  for(i=0; i<n_data; i++) {
    error_sum += residual_error(data[i].x, data[i].y, m, c);  
  }
  
  mean = error_sum / n_data;
  
  return sqrt(mean);
}

int main() {
  int i;
  double bm = 1.3;
  double bc = 10;
  double be;
  double dm[8];
  double dc[8];
  double e[8];
  double step = 0.01;
  double best_error = 999999999;
  int best_error_i;
  int minimum_found = 0;
  
  double om[] = {0,1,1, 1, 0,-1,-1,-1};
  double oc[] = {1,1,0,-1,-1,-1, 0, 1};

  be = rms_error(bm, bc);

  while(!minimum_found) {
    for(i=0;i<8;i++) {
      dm[i] = bm + (om[i] * step);
      dc[i] = bc + (oc[i] * step);    
    }
      
    for(i=0;i<8;i++) {
      e[i] = rms_error(dm[i], dc[i]);
      if(e[i] < best_error) {
        best_error = e[i];
        best_error_i = i;
      }
    }

    printf("best m,c is %lf,%lf with error %lf in direction %d\n", 
      dm[best_error_i], dc[best_error_i], best_error, best_error_i);
    if(best_error < be) {
      be = best_error;
      bm = dm[best_error_i];
      bc = dc[best_error_i];
    } else {
      minimum_found = 1;
    }
  }
  printf("minimum m,c is %lf,%lf with error %lf\n", bm, bc, be);

  return 0;
}

point_t data[] = {
  {69.55,109.75},{82.49,126.00},{73.41,90.18},{67.36,109.94},
  {67.46,104.57},{79.21,117.78},{83.96,119.97},{84.94,118.07},
  {65.65,114.21},{40.33,91.65},{73.06,97.09},{ 4.31,53.85},
  {20.47,63.01},{82.45,114.64},{25.75,65.48},{ 4.10,36.49},
  {47.48,98.15},{88.59,134.31},{10.94,39.20},{60.23,79.31},
  {78.02,103.60},{10.70,40.29},{62.39,87.84},{15.54,32.55},
  {77.26,109.27},{81.07,127.65},{88.01,143.11},{52.38,90.31},
  {76.56,101.30},{29.15,67.65},{83.07,124.14},{22.69,69.20},
  {90.06,128.19},{96.50,127.46},{90.83,128.02},{41.73,85.73},
  {41.66,106.17},{95.62,137.39},{ 9.36,29.63},{12.64,37.10},
  {70.62,104.75},{42.03,73.51},{63.21,113.80},{81.33,124.35},
  {53.87,82.62},{86.91,130.19},{63.46,113.32},{39.56,90.63},
  {69.24,108.60},{63.99,118.36},{12.37,45.70},{ 6.49,62.52},
  { 1.56,45.15},{38.03,77.54},{70.80,135.21},{38.18,51.17},
  {99.60,135.14},{62.16,104.23},{47.68,95.05},{ 3.25,27.43},
  {99.31,129.14},{61.73,113.71},{ 3.25,26.73},{32.76,66.42},
  {48.67,79.36},{84.78,128.77},{38.65,67.33},{ 0.80,34.21},
  {93.24,134.02},{39.34,66.82},{53.39,84.00},{48.60,98.90},
  {37.36,76.33},{91.34,107.09},{32.72,54.06},{ 6.45,30.49},
  {56.69,79.77},{58.85,103.05},{41.73,57.29},{23.69,53.32},
  {40.31,61.74},{91.61,142.70},{43.49,70.56},{ 7.96,38.18},
  {76.14,112.86},{38.75,80.32},{85.96,122.58},{94.02,117.62},
  {35.41,81.44},{ 8.60,38.48},{13.81,44.24},{43.90,83.10},
  {67.09,97.89},{ 0.84,35.05},{18.59,44.04},{75.56,114.31},
  {79.30,104.99},{18.28,58.25},{33.39,52.57},{57.92,88.83},
  {92.70,138.95},{35.22,59.27},{12.37,54.07},{77.64,120.58},
  {51.69,98.30},{ 3.08,59.17},{64.47,92.52},{73.87,124.43},
  {14.47,34.03},{17.22,44.74},{36.50,73.35},{67.31,83.29},
  {76.16,112.50},{42.17,79.90},{ 7.56,35.37},{60.82,81.69},
  {11.75,41.63},{28.78,56.74},{15.69,56.04},{82.91,118.83},
  {44.43,81.23},{63.99,107.20},{62.84,97.07},{19.76,73.24},
  {90.21,123.08},{33.34,81.64},{10.47,23.53},{40.46,56.75},
  {34.22,78.71},{18.71,44.63},{43.60,79.14},{24.23,58.80},
  {67.47,101.90},{48.63,91.75},{72.81,105.75},{88.91,127.98},
  {57.39,86.01},{66.09,107.04},{57.75,94.90},{76.89,120.83},
  {55.52,91.51},{84.88,118.21},{68.25,100.95},{66.47,99.24},
  {51.31,67.69},{84.99,123.94},{50.06,79.91},{37.80,67.84},
  {54.69,92.52},{16.22,55.49},{86.37,111.03},{30.91,46.45},
  {63.43,106.31},{70.20,84.54},{31.91,76.72},{90.00,135.68},
  {92.35,123.67},{22.35,52.74},{28.47,70.83},{67.34,114.48},
  {53.13,96.71},{30.69,53.93},{ 1.52,34.32},{93.32,129.06},
  {61.64,98.53},{ 1.92,36.51},{11.51,57.70},{74.33,125.22},
  {42.03,71.08},{45.82,71.16},{29.95,68.74},{60.77,91.81},
  {25.84,63.28},{74.85,98.76},{12.18,35.52},{ 0.53, 7.01},
  {43.18,72.12},{15.06,47.59},{84.35,121.98},{16.74,48.11},
  {62.33,93.70},{55.68,84.86},{80.90,141.51},{39.44,72.90},
  {98.35,129.23},{15.30,29.26},{54.09,96.36},{62.54,97.53},
  { 6.44,38.66},{25.47,67.10},{77.77,108.14},{87.36,117.94},
  {79.77,119.35},{ 3.05,41.52},{77.27,106.80},{68.79,85.05},
  {51.03,92.50},{65.78,111.52},{19.92,40.84},{29.77,52.54},
  {68.35,100.85},{29.13,90.37},{93.17,145.36},{47.78,83.46},
  {94.28,137.64},{70.78,99.74},{39.43,68.20},{ 5.01,41.62},
  {42.21,85.12},{91.52,118.43},{57.32,82.69},{84.06,116.74},
  {13.68,44.43},{32.37,83.14},{47.58,86.87},{97.08,140.06},
  {87.79,116.33},{18.34,45.01},{33.49,66.48},{28.05,52.62},
  {87.53,113.93},{57.96,96.28},{58.14,101.95},{24.36,68.95},
  {56.96,69.23},{33.23,72.65},{ 0.74,23.49},{ 0.95,17.40},
  {37.14,71.52},{43.83,47.65},{ 1.93,23.25},{17.94,59.56},
  {40.86,91.89},{86.10,123.19},{28.40,74.36},{98.46,140.86},
  {48.30,97.24},{41.19,75.72},{59.23,100.51},{82.12,117.91},
  {15.30,41.31},{32.19,63.39},{82.54,115.55},{67.67,112.02},
  { 9.27,22.60},{27.72,62.53},{16.72,51.86},{85.97,110.34},
  { 5.75,49.46},{92.36,121.87},{58.91,97.99},{60.80,122.23},
  {84.59,117.59},{17.22,48.04},{45.98,74.43},{45.49,72.64},
  {73.97,115.50},{36.98,68.82},{48.62,86.37},{ 1.15,39.08},
  {63.75,87.30},{47.73,83.53},{61.40,95.89},{73.64,118.05},
  {38.64,67.67},{43.20,77.02},{39.60,91.97},{54.20,107.77},
  {20.17,52.64},{34.13,64.24},{12.44,42.03},{96.39,133.92},
  {65.14,109.91},{23.60,54.59},{50.37,82.38},{81.89,120.43},
  {63.99,105.21},{93.04,131.70},{ 4.18,31.82},{83.21,117.34},
  {32.42,51.90},{90.61,131.16},{53.55,94.65},{40.28,87.87},
  {28.77,57.93},{16.42,67.35},{51.55,94.99},{49.23,100.27},
  {31.78,62.06},{41.90,60.19},{16.66,50.92},{ 3.44,40.11},
  {78.30,99.75},{72.42,109.87},{46.70,90.26},{29.38,65.03},
  {78.11,102.33},{37.84,70.54},{12.32,48.57},{ 9.50,35.44},
  {23.07,56.61},{45.44,74.98},{95.64,134.92},{48.34,72.10},
  {47.01,79.54},{80.60,131.78},{15.09,35.11},{42.92,68.47},
  {57.38,82.29},{60.86,93.16},{62.46,95.91},{54.70,97.49},
  {36.36,74.06},{ 8.09,25.90},{ 5.85,44.19},{38.30,66.20},
  {70.19,112.67},{78.03,106.54},{66.03,107.82},{32.06,61.90},
  {81.60,124.23},{70.12,104.43},{56.40,99.93},{43.80,80.11},
  {89.87,125.21},{80.44,108.93},{58.82,87.97},{89.25,142.14},
  {58.69,112.79},{21.67,58.38},{ 2.59,37.84},{ 6.13,24.42},
  {16.23,44.77},{86.06,108.32},{75.78,100.95},{81.40,131.21},
  {55.99,91.99},{28.38,81.16},{86.88,133.22},{46.21,89.32},
  {74.01,115.22},{12.22,44.51},{37.35,89.88},{ 6.42,38.02},
  { 8.61,26.03},{37.36,55.62},{87.11,126.94},{19.21,41.96},
  {25.20,77.94},{79.61,113.67},{54.41,98.50},{61.82,110.11},
  {85.61,115.86},{24.93,58.40},{35.39,44.09},{33.49,69.34},
  {49.69,100.35},{44.25,66.34},{85.06,133.27},{93.27,129.41},
  {72.00,121.37},{13.17,39.22},{ 2.16,30.70},{68.02,92.70},
  {96.98,125.43},{37.55,67.30},{70.57,112.32},{54.50,99.93},
  {31.09,75.50},{12.46,36.16},{25.06,50.39},{94.87,137.99},
  {58.93,111.08},{90.65,98.84},{55.73,96.50},{45.77,80.28},
  {49.16,96.94},{51.80,96.90},{32.37,65.91},{64.35,100.36},
  {48.24,92.24},{26.81,87.77},{ 4.39,42.73},{37.26,83.26},
  {37.43,55.12},{70.68,109.05},{50.11,78.05},{77.87,120.27},
  {80.96,114.78},{40.05,82.62},{50.04,79.49},{83.84,131.75},
  {66.92,107.75},{ 7.66,32.09},{43.74,89.16},{40.04,83.90},
  {59.30,96.76},{85.31,134.94},{17.80,37.06},{12.68,51.58},
  {48.15,68.89},{38.26,60.65},{28.33,74.79},{76.83,109.39},
  {66.30,93.18},{97.26,136.27},{62.33,99.09},{87.49,125.70},
  {61.48,94.99},{29.03,43.96},{77.05,111.94},{ 9.78,46.24},
  {27.44,58.69},{62.73,94.34},{16.71,43.42},{14.93,43.77},
  { 0.68,22.69},{65.77,109.78},{19.51,53.98},{65.47,110.22},
  {58.19,99.51},{75.13,103.75},{27.19,74.82},{35.55,64.34},
  {35.04,75.98},{11.60,40.08},{47.92,81.26},{ 0.18,42.25},
  {99.95,119.55},{26.02,78.84},{62.28,114.83},{97.84,143.83},
  {34.56,55.70},{ 9.09,42.49},{ 3.29,22.28},{ 0.84,17.59},
  {92.58,124.30},{24.72,46.45},{81.06,117.23},{76.80,122.16},
  {48.77,108.86},{23.37,61.68},{92.22,126.50},{17.62,48.17},
  {27.93,74.35},{13.41,36.73},{30.52,63.19},{76.22,117.56},
  {92.24,131.93},{71.86,101.64},{43.09,81.25},{ 4.19,28.60},
  {25.55,60.84},{ 1.12,38.30},{ 3.49,37.42},{54.81,103.22},
  {99.54,135.00},{ 9.27,34.74},{ 3.28,23.50},{75.97,111.24},
  {88.76,121.24},{57.91,82.79},{91.00,122.47},{81.48,114.56},
  {58.85,97.95},{71.87,124.31},{17.24,20.46},{ 6.26,56.33},
  {85.37,109.26},{54.23,89.03},{96.79,144.32},{20.79,42.69},
  {18.94,59.80},{ 2.75,36.74},{50.28,94.33},{40.91,53.65},
  {59.39,103.78},{59.40,93.82},{84.18,119.71},{47.49,92.25},
  {89.60,146.42},{51.01,85.72},{50.37,79.94},{64.24,101.65},
  {92.51,115.41},{12.55,61.56},{16.09,25.86},{74.59,101.57},
  {81.35,105.48},{ 7.51,46.64},{43.07,86.02},{21.08,66.66},
  {92.27,121.46},{73.70,118.02},{81.69,125.33},{11.16,45.09},
  {59.83,93.38},{ 2.91,29.45},{31.84,76.81},{88.01,124.87},
  {29.75,52.92},{12.86,40.04},{69.40,97.74},{61.94,72.23},
  {23.79,32.51},{74.62,107.41},{28.09,44.06},{89.09,125.45},
  {47.81,86.87},{81.75,109.19},{58.86,102.00},{74.55,108.25},
  {39.64,77.85},{74.85,111.51},{33.76,68.05},{ 6.60,43.02},
  {35.84,89.81},{40.19,78.38},{46.40,93.92},{29.16,62.38},
  {54.74,85.21},{78.87,122.15},{49.75,75.79},{55.47,79.07},
  { 3.43,40.72},{20.96,42.47},{79.02,105.19},{33.79,60.64},
  {81.67,108.28},{17.21,49.49},{71.04,94.10},{77.54,122.07},
  {84.62,119.41},{15.43,55.36},{15.93,25.05},{92.34,123.70},
  {84.07,121.11},{17.01,42.65},{51.33,102.58},{80.62,126.40},
  {54.96,105.40},{ 8.47,33.58},{16.50,48.25},{ 0.98,24.60},
  {45.67,87.89},{48.93,80.85},{22.40,57.56},{35.20,67.35},
  {41.86,86.51},{ 6.89,31.33},{21.82,64.73},{28.87,63.44},
  {78.94,109.32},{36.72,50.20},{41.34,81.49},{66.28,112.91},
  {17.34,61.88},{66.06,103.56},{64.68,124.14},{36.13,74.43},
  {39.66,61.89},{70.58,83.37},{ 6.95,11.43},{76.95,107.42},
  {35.95,90.10},{ 4.32,48.48},{ 5.39,34.25},{57.59,88.62},
  {35.82,74.26},{89.53,130.32},{86.54,115.27},{29.63,70.37},
  {50.03,85.13},{34.86,71.55},{97.06,131.15},{19.39,58.29},
  { 7.17,32.68},{53.19,68.07},{18.79,33.00},{88.43,134.27},
  { 5.17,31.19},{48.85,96.76},{30.00,48.93},{21.55,73.57},
  {72.47,112.69},{47.95,78.38},{44.88,75.15},{57.57,95.08},
  {97.40,147.20},{ 1.21,42.79},{90.26,120.05},{64.36,107.96},
  {64.72,106.18},{65.59,105.27},{73.49,135.32},{19.03,61.22},
  {11.24,40.24},{97.40,139.40},{74.21,98.54},{32.18,69.61},
  {39.52,63.81},{76.74,106.90},{28.67,59.16},{89.32,119.45},
  {42.33,82.49},{34.15,65.08},{21.22,53.22},{90.94,122.11},
  {18.22,47.86},{19.65,56.80},{93.57,140.88},{17.17,60.03},
  {71.87,96.59},{89.18,114.16},{55.57,103.39},{82.34,133.10},
  {84.11,119.96},{15.13,44.88},{86.57,120.73},{25.19,58.43},
  {81.28,114.48},{46.11,62.53},{13.15,29.99},{11.98,26.68},
  {87.28,127.49},{ 9.70,42.99},{10.88,58.70},{21.15,66.03},
  {17.48,15.33},{ 4.35,23.05},{92.16,130.06},{ 6.75,30.43},
  {60.28,103.77},{70.97,118.02},{92.36,124.08},{66.53,100.02},
  {80.58,104.82},{49.88,79.26},{33.61,72.16},{96.13,128.55},
  {26.22,52.79},{64.95,103.95},{82.30,119.75},{42.74,83.56},
  {18.32,62.53},{93.99,113.22},{86.81,137.00},{ 9.51,41.30},
  {60.15,81.16},{ 8.67,33.92},{28.28,62.77},{ 9.39,42.35},
  {16.41,52.59},{80.97,119.54},{68.46,104.84},{55.07,84.83},
  {20.45,42.93},{45.08,72.57},{ 4.42,35.65},{11.19,49.42},
  { 9.49,43.14},{88.39,125.46},{81.91,97.91},{56.08,91.22},
  {89.65,130.97},{36.57,72.90},{26.26,70.09},{45.10,85.40},
  {39.71,66.61},{83.75,100.02},{ 3.28,35.74},{17.70,54.39},
  { 5.15,30.01},{30.64,69.61},{69.57,127.65},{99.22,133.00},
  {88.04,116.17},{16.06,56.14},{20.91,48.31},{60.32,91.25},
  {32.85,58.04},{96.02,134.75},{71.98,115.61},{12.57,34.94},
  {99.02,133.66},{19.76,49.96},{54.66,85.89},{ 5.59,26.38},
  {10.70,47.22},{77.15,93.42},{34.36,75.40},{92.75,118.05},
  {46.49,71.98},{32.62,58.75},{44.82,67.43},{44.45,82.39},
  { 6.24,40.26},{61.91,87.88},{81.10,139.70},{91.45,134.03},
  {49.55,88.49},{50.25,78.04},{15.88,51.67},{ 6.46,40.58},
  {69.12,93.09},{ 1.71,17.10},{44.64,67.19},{74.75,98.18},
  {24.41,48.54},{50.14,93.92},{30.14,78.90},{80.35,130.69},
  {73.03,127.71},{70.44,104.69},{72.60,113.11},{ 3.51,26.65},
  {79.17,100.79},{33.29,79.41},{ 7.22,40.77},{ 3.93,41.54},
  {64.56,103.43},{ 4.94,38.18},{20.51,44.11},{43.35,94.14},
  {66.42,121.97},{64.50,114.86},{93.90,138.00},{82.29,117.57},
  {29.64,69.58},{85.02,121.03},{34.67,36.66},{89.82,144.66},
  {88.88,125.17},{ 2.05,32.44},{13.74,32.82},{88.10,121.12},
  {69.69,95.81},{21.23,76.71},{22.98,64.72},{32.56,76.86},
  {31.48,40.27},{51.15,84.40},{79.73,121.72},{90.80,138.87},
  {21.63,44.71},{72.67,121.47},{58.28,87.74},{88.03,117.66},
  {28.82,56.01},{17.69,45.02},{83.10,98.73},{52.34,92.64},
  {58.27,78.50},{44.59,76.24},{78.37,112.91},{49.42,74.18},
  {99.90,155.27},{49.07,87.85},{ 8.86,56.73},{29.45,84.57},
  { 9.80,46.04},{22.57,57.13},{43.72,75.81},{41.87,82.50},
  {79.48,110.27},{56.20,104.15},{44.28,74.83},{56.91,94.93},
  {78.70,137.33},{66.57,122.94},{54.64,83.24},{67.36,116.12},
  {17.29,59.00},{52.07,71.79},{95.54,137.22},{38.62,85.99},
  {23.94,60.94},{19.61,53.29},{20.90,71.10},{69.36,108.22},
  {69.86,103.60},{ 5.04,23.95},{97.79,132.39},{34.27,64.24},
  {17.47,54.62},{88.78,119.32},{89.91,124.05},{54.84,79.45},
  {69.05,98.55},{74.54,120.10},{49.76,89.67},{35.46,72.16},
  {69.62,98.59},{83.34,133.86},{54.68,86.16},{23.52,73.77},
  {74.04,115.19},{ 3.75,40.68},{32.42,65.37},{87.83,126.33},
  {27.40,58.91},{83.93,142.46},{56.68,83.59},{25.24,69.34},
  {25.08,41.09},{65.63,71.81},{57.89,102.96},{31.77,74.32},
  {55.91,113.32},{93.78,139.50},{20.94,57.51},{92.89,139.36},
  {39.40,58.69},{54.86,93.75},{75.41,107.55},{66.61,126.79},
  {68.03,101.23},{70.69,86.71},{72.39,105.02},{60.16,74.26},
  {36.27,63.07},{71.31,107.17},{50.42,75.32},{91.28,126.63},
  {78.41,99.63},{ 3.60,54.88},{ 9.33,33.69},{24.50,60.71},
  {10.62,34.97},{88.83,136.13},{54.23,95.04},{50.71,81.40},
  {77.06,100.88},{ 6.22,50.18},{54.22,96.78},{68.60,97.04},
  {70.71,127.48},{46.58,77.92},{83.72,126.16},{27.37,57.73},
  {48.55,85.28},{56.77,105.30},{49.41,87.36},{ 2.22,17.97},
  {92.79,128.82},{22.49,43.05},{58.67,102.30},{30.16,46.83},
  {34.07,79.67},{24.45,41.48},{41.34,80.76},{69.37,118.96},
  {70.68,110.91},{29.30,40.58},{ 5.86,58.24},{ 8.16,45.08},
  {84.51,117.95},{44.28,78.60},{13.57,47.07},{39.03,73.05},
  {82.30,136.30},{14.82,57.01},{26.41,51.33},{48.49,91.37},
  {81.11,109.85},{88.29,153.37},{64.89,105.58},{60.10,85.15},
  {43.12,69.86},{48.20,68.23},{55.28,90.13},{37.74,52.64},
  { 8.06,29.92},{15.52,57.59},{ 1.94,27.21},{90.10,115.14},
  {48.90,81.08},{86.44,108.80},{67.40,109.41},{41.71,83.72},
  {14.69,43.71},{61.51,106.54},{71.32,99.09},{93.06,151.60},
  {60.75,87.61},{ 9.36,31.65},{66.25,95.48},{65.76,94.96},
  {70.71,110.38},{20.35,44.97},{14.86,41.10},{80.21,105.76},
  {92.71,144.38},{13.61,43.77},{12.37,28.55},{56.53,91.05},
  {43.79,94.09},{25.36,56.85},{ 2.96,30.91},{87.47,136.13},
  {98.55,128.18},{81.71,111.23},{19.75,46.92},{82.11,130.77},
  { 6.13,34.78},{77.45,117.85},{52.83,108.75},{19.42,56.80},
  {94.77,140.73},{14.39,55.90},{57.45,93.01},{71.80,96.57},
  {55.81,86.08},{80.20,129.40},{89.99,117.11},{94.19,146.57},
  {94.21,115.91},{ 8.36,22.08},{64.61,101.95},{27.04,74.27},
  {89.17,130.69},{15.25,39.18},{21.17,56.41},{21.76,33.00},
  {21.29,55.17},{40.97,49.51},{ 4.44,29.44},{81.74,114.05},
  {67.54,95.87},{29.28,52.96},{82.89,122.97},{22.14,46.46},
  {27.17,57.15},{49.01,87.40},{63.91,102.07},{46.74,79.27},
  {99.34,145.40},{ 9.32,27.46},{53.55,94.13},{19.70,43.72},
  {40.25,79.20},{33.40,67.33},{74.58,108.29},{40.54,79.62},
  {36.74,69.66},{30.10,59.92},{27.88,63.00},{ 4.64,43.53},
  {75.03,103.87},{74.77,127.06},{66.60,114.93},{87.16,124.16},
  { 6.81,28.47},{42.40,86.21},{ 0.08,24.11},{ 6.86,18.16},
  {40.88,70.12},{78.57,117.87},{95.65,124.42},{90.63,115.65},
  {16.47,59.18},{ 3.13,33.14},{91.30,132.46},{ 1.56,22.66},
  { 6.58,24.89},{52.64,96.10},{53.01,90.36},{ 1.58,27.52},
  {44.16,84.03},{84.21,136.32},{ 3.91,27.63},{ 4.98,39.00},
  {70.20,119.27},{23.43,50.81},{25.65,79.41},{18.71,47.71},
  {59.22,82.95},{64.06,121.49},{36.35,84.93},{47.47,85.34},
  {19.65,56.10},{32.69,62.39},{56.33,91.95},{39.65,68.39},
  {60.54,105.25},{37.70,73.96},{32.05,72.87},{ 9.07,40.47},
  {38.72,72.70},{60.45,92.18},{72.56,107.68},{96.16,140.72},
  {90.09,162.64},{ 2.79,47.27},{17.09,43.82},{70.37,104.71},
  { 5.84,41.35},{34.24,62.82},{15.75,46.58},{13.51,41.47}
};
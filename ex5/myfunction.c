#define min(a,b) (a < b ? a : b)
#define max(a,b) (a > b ? a : b)

typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char dummy;
} pixel;

typedef struct {
	int red;
	int green;
	int blue;
	int dummy;
	// int num;
} pixel_sum;

/*
* Apply the kernel over each pixel.
* Ignore pixels where the kernel exceeds bounds. These are pixels with row index smaller than kernelSize/2 and/or
* column index smaller than kernelSize/2
*/
void smooth(int dim1, pixel *src1, pixel *dst1, int kernelType, int kernelScale) {
	int dim = dim1;
	register pixel* src = src1;
	pixel* dst = dst1;
	int j;
	int i;
	int lim = dim - 1;
	int index = n + 1;
	register int index1 = 0;
	pixel_sum right, mid;
	pixel current_pixel;
	pixel_sum sum;
	register pixel p;
	pixel min, max;
	if (kernelType == 1 && kernelScale == 7) {
		register int currSum;
		for (i = 1; i < lim; ++i) {
			p = src[index1];
			sum.red = p.red;
			sum.green = p.green;
			sum.blue = p.blue;
			int min_intensity = 766;
			int max_intensity = -1;
			currSum = p.red + p.green + p.blue;
			min_intensity = currSum;
			min = p;
			max_intensity = currSum;
			max = p;
			++index1;
			p = src[index1];
			mid.red = p.red;
			mid.green = p.green;
			mid.blue = p.blue;
			currSum = p.red + p.green + p.blue;
			if (currSum <= min_intensity) {
				min_intensity = currSum;
				min = p;
			}
			if (currSum > max_intensity) {
				max_intensity = currSum;
				max = p;
			}
			++index1;
			p = src[index1];
			right.red = p.red;
			right.green = p.green;
			right.blue = p.blue;
			currSum = p.red + p.green + p.blue;
			if (currSum <= min_intensity) {
				min_intensity = currSum;
				min = p;
			}
			if (currSum > max_intensity) {
				max_intensity = currSum;
				max = p;
			}
			index1 += (n - 2);
			p = src[index1];
			sum.red += p.red;
			sum.green += p.green;
			sum.blue += p.blue;
			currSum = p.red + p.green + p.blue;
			if (currSum <= min_intensity) {
				min_intensity = currSum;
				min = p;
			}
			if (currSum > max_intensity) {
				max_intensity = currSum;
				max = p;
			}
			++index1;
			p = src[index1];
			mid.red += p.red;
			mid.green += p.green;
			mid.blue += p.blue;
			currSum = p.red + p.green + p.blue;
			if (currSum <= min_intensity) {
				min_intensity = currSum;
				min = p;
			}
			if (currSum > max_intensity) {
				max_intensity = currSum;
				max = p;
			}
			++index1;
			p = src[index1];
			right.red += p.red;
			right.green += p.green;
			right.blue += p.blue;
			currSum = p.red + p.green + p.blue;
			if (currSum <= min_intensity) {
				min_intensity = currSum;
				min = p;
			}
			if (currSum > max_intensity) {
				max_intensity = currSum;
				max = p;
			}
			index1 += (n - 2);
			p = src[index1];
			sum.red += p.red;
			sum.green += p.green;
			sum.blue += p.blue;
			currSum = p.red + p.green + p.blue;
			if (currSum <= min_intensity) {
				min_intensity = currSum;
				min = p;
			}
			if (currSum > max_intensity) {
				max_intensity = currSum;
				max = p;
			}
			++index1;
			p = src[index1];
			mid.red += p.red;
			mid.green += p.green;
			mid.blue += p.blue;
			currSum = p.red + p.green + p.blue;
			if (currSum <= min_intensity) {
				min_intensity = currSum;
				min = p;
			}
			if (currSum > max_intensity) {
				max_intensity = currSum;
				max = p;
			}
			++index1;
			p = src[index1];
			right.red += p.red;
			right.green += p.green;
			right.blue += p.blue;
			currSum = p.red + p.green + p.blue;
			if (currSum <= min_intensity) {
				min_intensity = currSum;
				min = p;
			}
			if (currSum > max_intensity) {
				max_intensity = currSum;
				max = p;
			}
			sum.red += (right.red + mid.red);
			sum.blue += (right.blue + mid.blue);
			sum.green += (right.green + mid.green);
			sum.red -= max.red;
			sum.green -= max.green;
			sum.blue -= max.blue;
			sum.red -= min.red;
			sum.green -= min.green;
			sum.blue -= min.blue;
			sum.red /= 7;
			sum.green /= 7;
			sum.blue /= 7;
			current_pixel.red = (min(max(sum.red, 0), 255));
			current_pixel.green = (min(max(sum.green, 0), 255));
			current_pixel.blue = (min(max(sum.blue, 0), 255));
			dst[index] = current_pixel;
			++index;
			index1 -= ((n << 1) + 1);
			for (j = 2; j < lim ; ++j) {
				sum.red = mid.red + right.red;
				sum.blue = mid.blue + right.blue;
				sum.green = mid.green + right.green;
				mid = right;
				int min_intensity = 766;
				int max_intensity = -1;
				// find min and max coordinates
				pixel loop_pixel = src[index1];
				currSum = loop_pixel.red + loop_pixel.green + loop_pixel.blue;

				min_intensity = currSum;
				min = loop_pixel;
				max_intensity = currSum;
				max = loop_pixel;

				++index1;
				loop_pixel = src[index1];
				currSum = loop_pixel.red + loop_pixel.green + loop_pixel.blue;
				if (currSum <= min_intensity) {
					min_intensity = currSum;
					min = loop_pixel;
				}
				if (currSum > max_intensity) {
					max_intensity = currSum;
					max = loop_pixel;
				}
				++index1;
				loop_pixel = src[index1];
				currSum = loop_pixel.red + loop_pixel.green + loop_pixel.blue;
				if (currSum <= min_intensity) {
					min_intensity = currSum;
					min = loop_pixel;
				}
				if (currSum > max_intensity) {
					max_intensity = currSum;
					max = loop_pixel;
				}
				right.red = loop_pixel.red;
				right.green = loop_pixel.green;
				right.blue = loop_pixel.blue;
				index1 += (n - 2);
				loop_pixel = src[index1];
				currSum = loop_pixel.red + loop_pixel.green + loop_pixel.blue;
				if (currSum <= min_intensity) {
					min_intensity = currSum;
					min = loop_pixel;
				}
				if (currSum > max_intensity) {
					max_intensity = currSum;
					max = loop_pixel;
				}
				++index1;
				loop_pixel = src[index1];
				currSum = loop_pixel.red + loop_pixel.green + loop_pixel.blue;
				if (currSum <= min_intensity) {
					min_intensity = currSum;
					min = loop_pixel;
				}
				if (currSum > max_intensity) {
					max_intensity = currSum;
					max = loop_pixel;
				}
				++index1;
				loop_pixel = src[index1];
				currSum = loop_pixel.red + loop_pixel.green + loop_pixel.blue;
				if (currSum <= min_intensity) {
					min_intensity = currSum;
					min = loop_pixel;
				}
				if (currSum > max_intensity) {
					max_intensity = currSum;
					max = loop_pixel;
				}
				right.red += loop_pixel.red;
				right.green += loop_pixel.green;
				right.blue += loop_pixel.blue;
				index1 += (n - 2);
				loop_pixel = src[index1];
				currSum = loop_pixel.red + loop_pixel.green + loop_pixel.blue;
				if (currSum <= min_intensity) {
					min_intensity = currSum;
					min = loop_pixel;
				}
				if (currSum > max_intensity) {
					max_intensity = currSum;
					max = loop_pixel;
				}
				++index1;
				loop_pixel = src[index1];
				currSum = loop_pixel.red + loop_pixel.green + loop_pixel.blue;
				if (currSum <= min_intensity) {
					min_intensity = currSum;
					min = loop_pixel;
				}
				if (currSum > max_intensity) {
					max_intensity = currSum;
					max = loop_pixel;
				}
				++index1;
				loop_pixel = src[index1];
				currSum = loop_pixel.red + loop_pixel.green + loop_pixel.blue;
				if (currSum <= min_intensity) {
					min_intensity = currSum;
					min = loop_pixel;
				}
				if (currSum > max_intensity) {
					max_intensity = currSum;
					max = loop_pixel;
				}
				right.red += loop_pixel.red;
				right.green += loop_pixel.green;
				right.blue += loop_pixel.blue;
				sum.red += right.red;
				sum.green += right.green;
				sum.blue += right.blue;

				sum.red -= max.red;
				sum.green -= max.green;
				sum.blue -= max.blue;
				sum.red -= min.red;
				sum.green -= min.green;
				sum.blue -= min.blue;

				sum.red /= 7;
				sum.green /= 7;
				sum.blue /= 7;
				current_pixel.red = (min(max(sum.red, 0), 255));
				current_pixel.green = (min(max(sum.green, 0), 255));
				current_pixel.blue = (min(max(sum.blue, 0), 255));
				dst[index] = current_pixel;
				++index;
				index1 -= ((n << 1) + 1);
			}
			index += 2;
			index1 += 2;
		}
	} else if (kernelType == 1) {
		for (i = 1; i < lim; ++i) {
			p = src[index1];
			sum.red = p.red;
			sum.green = p.green;
			sum.blue = p.blue;
			++index1;
			p = src[index1];
			mid.red = p.red;
			mid.green = p.green;
			mid.blue = p.blue;
			++index1;
			p = src[index1];
			right.red = p.red;
			right.green = p.green;
			right.blue = p.blue;
			index1 += (n - 2);
			p = src[index1];
			sum.red += p.red;
			sum.green += p.green;
			sum.blue += p.blue;
			++index1;
			p = src[index1];
			mid.red += p.red;
			mid.green += p.green;
			mid.blue += p.blue;
			++index1;
			p = src[index1];
			right.red += p.red;
			right.green += p.green;
			right.blue += p.blue;
			index1 += (n - 2);
			p = src[index1];
			sum.red += p.red;
			sum.green += p.green;
			sum.blue += p.blue;
			++index1;
			p = src[index1];
			mid.red += p.red;
			mid.green += p.green;
			mid.blue += p.blue;
			++index1;
			p = src[index1];
			right.red += p.red;
			right.green += p.green;
			right.blue += p.blue;
			sum.red += (right.red + mid.red);
			sum.blue += (right.blue + mid.blue);
			sum.green += (right.green + mid.green);
			sum.red /= 9;
			sum.green /= 9;
			sum.blue /= 9;
			current_pixel.red = (min(max(sum.red, 0), 255));
			current_pixel.green = (min(max(sum.green, 0), 255));
			current_pixel.blue = (min(max(sum.blue, 0), 255));
			dst[index] = current_pixel;
			++index;
			index1 -= ((n << 1) - 1);
			for (j = 2; j < lim ; ++j) {
				sum.red = mid.red + right.red;
				sum.blue = mid.blue + right.blue;
				sum.green = mid.green + right.green;
				mid = right;
				p = src[index1];
				right.red = p.red;
				right.green = p.green;
				right.blue = p.blue;
				index1 += n;
				p = src[index1];
				right.red += p.red;
				right.green += p.green;
				right.blue += p.blue;
				index1 += n;
				p = src[index1];
				right.red += p.red;
				right.green += p.green;
				right.blue += p.blue;
				sum.red += right.red;
				sum.green += right.green;
				sum.blue += right.blue;
				sum.red /= 9;
				sum.green /= 9;
				sum.blue /= 9;
				current_pixel.red = (min(max(sum.red, 0), 255));
				current_pixel.green = (min(max(sum.green, 0), 255));
				current_pixel.blue = (min(max(sum.blue, 0), 255));
				dst[index] = current_pixel;
				++index;
				index1 -= ((n << 1) - 1);
			}
			index += 2;
		}
	}
	else {
		pixel midPixel, rightPixel;
		for (i = 1; i < lim; ++i) {
			p = src[index1];
			sum.red = -p.red;
			sum.green = -p.green;
			sum.blue = -p.blue;
			++index1;
			p = src[index1];
			mid.red = -p.red;
			mid.green = -p.green;
			mid.blue = -p.blue;
			++index1;
			p = src[index1];
			right.red = -p.red;
			right.green = -p.green;
			right.blue = -p.blue;
			index1 += (n - 2);
			p = src[index1];
			sum.red -= p.red;
			sum.green -= p.green;
			sum.blue -= p.blue;
			++index1;
			p = src[index1];
			mid.red += 9 * p.red;
			mid.green += 9 * p.green;
			mid.blue += 9 * p.blue;
			midPixel = p;
			++index1;
			p = src[index1];
			right.red -= p.red;
			right.green -= p.green;
			right.blue -= p.blue;
			rightPixel = p;
			index1 += (n - 2);
			p = src[index1];
			sum.red -= p.red;
			sum.green -= p.green;
			sum.blue -= p.blue;
			++index1;
			p = src[index1];
			mid.red -= p.red;
			mid.green -= p.green;
			mid.blue -= p.blue;
			++index1;
			p = src[index1];
			right.red -= p.red;
			right.green -= p.green;
			right.blue -= p.blue;
			sum.red += (right.red + mid.red);
			sum.blue += (right.blue + mid.blue);
			sum.green += (right.green + mid.green);
			current_pixel.red = (min(max(sum.red, 0), 255));
			current_pixel.green = (min(max(sum.green, 0), 255));
			current_pixel.blue = (min(max(sum.blue, 0), 255));
			dst[index] = current_pixel;
			++index;
			index1 -= ((n << 1) - 1);
			for (j = 2; j < lim ; ++j) {
				right.red += 10 * rightPixel.red;
				right.blue += 10 * rightPixel.blue;
				right.green += 10 * rightPixel.green;
				sum.red = mid.red + right.red - 10 * midPixel.red;
				sum.blue = mid.blue + right.blue - 10 * midPixel.blue;
				sum.green = mid.green + right.green - 10 * midPixel.green;
				mid = right;
				midPixel = rightPixel;
				p = src[index1];
				right.red = - p.red;
				right.green = - p.green;
				right.blue = - p.blue;
				index1 += n;
				p = src[index1];
				right.red -= p.red;
				right.green -= p.green;
				right.blue -= p.blue;
				rightPixel = p;
				index1 += n;
				p = src[index1];
				right.red -= p.red;
				right.green -= p.green;
				right.blue -= p.blue;
				sum.red += right.red;
				sum.green += right.green;
				sum.blue += right.blue;
				current_pixel.red = (min(max(sum.red, 0), 255));
				current_pixel.green = (min(max(sum.green, 0), 255));
				current_pixel.blue = (min(max(sum.blue, 0), 255));
				dst[index] = current_pixel;
				++index;
				index1 -= ((n << 1) - 1);
			}
			index += 2;
		}

	}

}


void doConvolution(Image * image, int kernelType, int kernelScale) {
	int lim = m * n;
	int mallSize = lim * sizeof(pixel);
	pixel* pixelsImg = malloc(mallSize);
	pixel* backupOrg = malloc(mallSize);

	Image localImg = *image;
	pixel p;
	int currIndex = 0;
	int iter;
	for (iter = 0; iter < lim; ++iter) {
		p.red = localImg.data[currIndex];
		p.green = localImg.data[++currIndex];
		p.blue = localImg.data[++currIndex];
		pixelsImg[iter] = p;
		++currIndex;
	}
	memcpy(backupOrg, pixelsImg, mallSize);

	smooth(m, backupOrg, pixelsImg, kernelType, kernelScale);

	currIndex = 0;
	for (iter = 0; iter < lim; ++iter) {
		p = pixelsImg[iter];
		localImg.data[currIndex] = p.red;
		localImg.data[++currIndex] = p.green;
		localImg.data[++currIndex] = p.blue;
		++currIndex;
	}
	*image = localImg;
	free(pixelsImg);
	free(backupOrg);
}

void myfunction(Image * image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName, char* filteredBlurRsltImgName, char* filteredSharpRsltImgName, char flag) {
	if (flag == '1') {
		// blur image
		doConvolution(image, 1, 9);

		// write result image to file
		writeBMP(image, srcImgpName, blurRsltImgName);

		// sharpen the resulting image
		doConvolution(image, 0, 1);

		// write result image to file
		writeBMP(image, srcImgpName, sharpRsltImgName);
	} else {
		// apply extermum filtered kernel to blur image
		doConvolution(image, 1, 7);

		// write result image to file
		writeBMP(image, srcImgpName, filteredBlurRsltImgName);

		// sharpen the resulting image
		doConvolution(image, 0, 1);

		// write result image to file
		writeBMP(image, srcImgpName, filteredSharpRsltImgName);
	}
}

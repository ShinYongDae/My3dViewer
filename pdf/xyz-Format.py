def write_zygo_ascii(file, phase, dx, wavelength=0.6328, intensity=None):
    """Write a Zygo ASCII interferogram file.

    Parameters
    ----------
    file : path_like
        filename
    phase : ndarray
        array of phase values, nm
    dx : ndarray
        inter-sample spacing, mm
    wavelength : float, optional
        wavelength of light, um
    intensity : ndarray, optional
        intensity data

    """
    # construct the header
    timestamp = datetime.datetime.now()
    line1 = 'Zygo ASCII Data File - Format 2'
    line2 = '0 0 0 0 ' + timestamp.strftime('"%a %b %d %H:%M:%S %Y').ljust(30, ' ') + '"'
    if intensity is None:
        line3 = '0 0 0 0 0 0'
    else:
        raise NotImplementedError('writing of ASCII files with nonempty intensity not yet supported.')
    px, py = phase.shape
    ox = 0
    oy = 0
    line4 = f'{oy} {ox} {py} {px}'
    line5 = '"' + ' ' * 81 + '"'
    line6 = '"' + ' ' * 39 + '"'
    line7 = '"' + ' ' * 39 + '"'

    timestamp_int = int(str(timestamp.timestamp()).split('.')[0])
    res = dx * 1e3
    line8 = f'0 0.5 {wavelength*1e-6} 0 1 0 {res} {timestamp_int}'  # end is timestamp in integer seconds
    line9 = f'{py} {px} 0 0 0 0 ' + '"' + ' ' * 9 + '"'
    line10 = '0 0 0 0 0 0 0 0 0 0'
    line11 = '1 1 20 2 0 0 0 0 0'
    line12 = '0 ' + '"' + ' ' * 12 + '"'
    line13 = '1 0'
    line14 = '"' + ' ' * 7 + '"'

    header_lines = (line1,
                    line2,
                    line3,
                    line4,
                    line5,
                    line6,
                    line7,
                    line8,
                    line9,
                    line10,
                    line11,
                    line12,
                    line13,
                    line14)
    header = '\n'.join(header_lines) + '\n'

    if intensity is None:
        line15 = '#'

    line16 = '#'

    # process the phase and write out
    coef = ZYGO_PHASE_RES_FACTORS[1]
    encoded_phase = phase * (coef / wavelength / wavelength / 0.5)
    encoded_phase[np.isnan(encoded_phase)] = ZYGO_INVALID_PHASE
    encoded_phase = encoded_phase.astype(np.int64)
    encoded_phase = encoded_phase.flatten()
    npts = encoded_phase.shape[0]
    fits_by_ten = npts // 10
    boundary = 10 * fits_by_ten

    # create an in-memory buffer and write out the phase to it
    s = StringIO()
    s.write(header)
    s.write('\n'.join([line15, line16, '']))
    truenp.savetxt(s, encoded_phase[:boundary].reshape(-1, 10), fmt='%d', delimiter=' ', newline=' \n')
    tail = ' '.join((str(d) for d in encoded_phase[boundary:]))
    s.write(tail)
    s.write('\n#\n')
    s.seek(0)

    if not isinstance(file, IOBase):
        with open(file, 'w') as fd:
            shutil.copyfileobj(s, fd)
    else:
        shutil.copyfileobj(s, file)


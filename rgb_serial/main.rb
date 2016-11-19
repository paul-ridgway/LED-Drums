require_relative 'rgb'
require "unimidi"

LEDS = 149

# Prompt the user
input = UniMIDI::Input.use(:first)

@rgb = Rgb.new(LEDS)

@rgb.start

HIHAT_TOP = 46
HIHAT_TOP_CLOSED = 42
HIHAT_RIM = 26
HIHAT_RIM_CLOSED = 22
HIHAT_PEDAL = 44
CRASH_TOP = 49
CRASH_RIM = 55
RIDE_TOP = 51
RIDE_RIM = 59
RIDE_BELL = 53
SPLASH_TOP = 57
SPLASH_RIM = 52
BASS = 36
SNARE = 38
SNARE_RIM = 37
SNARE_RIM2 = 40
TOM1 = 48
TOM1_RIM = 50
TOM2 = 45
TOM2_RIM = 47
TOM3 = 43
TOM3_RIM = 58
TOM4 = 41
TOM4_RIM = 39

@rgb.add_trigger(BASS, (58..128).step(2).to_a, 0.1, 0.1, 0.1, 0.7)
@rgb.add_trigger(BASS, (87..109).step(1).to_a, 0.0, 1.0, 1.0, 0.9)

@rgb.add_trigger(SNARE, [129, 132, 54, 57, 14, 97] , 1.0, 1.0, 1.0, 0.2)
@rgb.add_trigger(SNARE_RIM, [129, 132, 54, 57, 14, 97] , 1.0, 1.0, 0.0, 0.2)
@rgb.add_trigger(SNARE_RIM2, [129, 132, 54, 57, 14, 97] , 1.0, 0.0, 1.0, 0.2)
@rgb.add_trigger(SNARE, (1..58).step(2).to_a , 0.1, 0.0, 0.0, 0.4)
@rgb.add_trigger(SNARE, (128..LEDS).step(2).to_a , 0.1, 0.0, 0.0, 0.4)
@rgb.add_trigger(SNARE_RIM, (1..58).step(2).to_a , 0.1, 0.0, 0.0, 0.4)
@rgb.add_trigger(SNARE_RIM, (128..LEDS).step(2).to_a , 0.1, 0.0, 0.0, 0.4)
@rgb.add_trigger(SNARE_RIM2, (1..58).step(2).to_a , 0.1, 0.0, 0.0, 0.4)
@rgb.add_trigger(SNARE_RIM2, (128..LEDS).step(2).to_a , 0.1, 0.0, 0.0, 0.4)

hi_hat_round = (1..58).step(2).to_a + (128..LEDS).step(2).to_a

@rgb.add_trigger(HIHAT_RIM, 		(132..143).to_a , 0.0, 1.0, 0.5, 0.9)
@rgb.add_trigger(HIHAT_TOP, 		(132..143).to_a , 0.0, 0.5, 1.0, 0.9)
@rgb.add_trigger(HIHAT_PEDAL, 		(132..143).to_a , 0.0, 1.0, 1.0, 0.9)
@rgb.add_trigger(HIHAT_RIM_CLOSED, 	(132..143).to_a , 1.0, 0.5, 0.75, 0.9)
@rgb.add_trigger(HIHAT_TOP_CLOSED, 	(132..143).to_a , 0.5, 1.0, 0.75, 0.9)
@rgb.add_trigger(HIHAT_RIM, 		hi_hat_round.to_a , 0.0, 0.1, 0.0, 0.9)
@rgb.add_trigger(HIHAT_TOP, 		hi_hat_round.to_a , 0.0, 0.1, 0.0, 0.9)
@rgb.add_trigger(HIHAT_PEDAL, 		hi_hat_round.to_a , 0.0, 0.1, 0.0, 0.9)
@rgb.add_trigger(HIHAT_RIM_CLOSED, 	hi_hat_round.to_a , 0.0, 0.1, 0.0, 0.9)
@rgb.add_trigger(HIHAT_TOP_CLOSED, 	hi_hat_round.to_a , 0.0, 0.1, 0.0, 0.9)
@rgb.add_trigger(HIHAT_RIM, 		(115..131).step(2).to_a , 0.0, 1.0, 0.0, 0.7)
@rgb.add_trigger(HIHAT_TOP, 		(115..131).step(2).to_a , 0.0, 1.0, 0.0, 0.7)
@rgb.add_trigger(HIHAT_PEDAL, 		(115..131).step(2).to_a , 0.0, 1.0, 0.0, 0.7)
@rgb.add_trigger(HIHAT_RIM_CLOSED, 	(115..131).step(2).to_a , 0.0, 1.0, 0.0, 0.7)
@rgb.add_trigger(HIHAT_TOP_CLOSED, 	(115..131).step(2).to_a , 0.0, 1.0, 0.0, 0.7)

@rgb.add_trigger(CRASH_TOP, (0..3).to_a, 0.5, 1.0, 0.0, 0.9)
@rgb.add_trigger(CRASH_TOP, (143..LEDS).to_a, 0.5, 1.0, 0.0, 0.9)
@rgb.add_trigger(CRASH_RIM, (0..3).to_a, 1.0, 0.5, 0.0, 0.9)
@rgb.add_trigger(CRASH_RIM, (143..LEDS).to_a, 1.0, 0.5, 0.0, 0.9)
@rgb.add_trigger(CRASH_TOP, (107..122).step(2).to_a , 1.0, 0.0, 0.0, 0.7)
@rgb.add_trigger(CRASH_RIM, (107..122).step(2).to_a , 1.0, 0.0, 0.0, 0.7)


@rgb.add_trigger(TOM1, (1..15).to_a, 0.0, 1.0, 0.0, 0.9)
@rgb.add_trigger(TOM1_RIM, (1..15).to_a, 1.0, 0.0, 1.0, 0.9)
@rgb.add_trigger(TOM2, (12..27).to_a, 0.0, 0.0, 1.0, 0.9)
@rgb.add_trigger(TOM2_RIM, (12..27).to_a, 1.0, 1.0, 0.0, 0.9)

@rgb.add_trigger(RIDE_TOP, (22..35).to_a, 0.0, 0.3, 1.0, 0.9)
@rgb.add_trigger(RIDE_BELL, (22..35).to_a, 1.0, 0.3, 0.0, 0.9)
@rgb.add_trigger(RIDE_RIM, (22..35).to_a, 0.3, 1.0, 0.0, 0.9)

@rgb.add_trigger(RIDE_TOP, (71..91).step(2).to_a, 0.0, 0.0, 1.0, 0.7)
@rgb.add_trigger(RIDE_BELL, (71..91).step(2).to_a, 0.0, 0.0, 1.0, 0.7)
@rgb.add_trigger(RIDE_RIM, (71..91).step(2).to_a, 0.0, 0.0, 1.0, 0.7)

@rgb.add_trigger(TOM3, (27..45).to_a, 1.0, 0.0, 1.0, 0.9)
@rgb.add_trigger(TOM3_RIM, (27..45).to_a, 0.0, 1.0, 0.0, 0.9)

@rgb.add_trigger(SPLASH_TOP, (43..46).to_a, 1.0, 0.5, 0.0, 0.9)
@rgb.add_trigger(SPLASH_RIM, (43..46).to_a, 0.5, 1.0, 0.0, 0.9)

@rgb.add_trigger(SPLASH_TOP, (57..73).step(2).to_a, 0.0, 1.0, 0.0, 0.7)
@rgb.add_trigger(SPLASH_RIM, (57..73).step(2).to_a, 0.0, 1.0, 0.0, 0.7)

@rgb.add_trigger(TOM4, (45..67).to_a, 0.0, 1.0, 1.0, 0.9)
@rgb.add_trigger(TOM4_RIM, (45..67).to_a, 1.0, 0.0, 0.0, 0.9)


def read_char
  STDIN.echo = false
  STDIN.raw!

  input = STDIN.getc.chr
  if input == "\e" then
    input << STDIN.read_nonblock(3) rescue nil
    input << STDIN.read_nonblock(2) rescue nil
  end
ensure
  STDIN.echo = true
  STDIN.cooked!

  return input
end

while(true) 
	# LEDS.times.each do |i|
	# 	# @rgb.add(i, 0, 1.0, 0, 0.95)
	# 	# @rgb.set(i, rand(256).to_f / 256.0, rand(256).to_f / 256.0, rand(256).to_f / 256.0)
	# 	# @rgb.set(i, rand(256).to_f / 256.0, rand(256).to_f / 256.0, rand(256).to_f / 256.0, rand(256).to_f / 256.0)
	# 	# @rgb.set(rand(LEDS + 1), rand(256).to_f / 256.0, rand(256).to_f / 256.0, rand(256).to_f / 256.0, (128 + rand(128)).to_f / 256.0)
	# 	# @rgb.add(rand(LEDS), rand(256).to_f / 256.0, rand(256).to_f / 256.0, rand(256).to_f / 256.0, (128 + rand(128)).to_f / 256.0)
	# 	@rgb.add(rand(LEDS + 1), 0, 0.5, 1.0, 0.95)
	# 	sleep 0.02
	# 	# sleep 0.001
	# 	# @rgb.set(i, 0, 0.33, 0)
	# end
	# char = read_char
	# char.each_byte.each do |i|
	# 	if i == 3
	# 		puts "Bye!"
	# 		exit 0 
	# 	end
	# 	puts i
	# 	# @rgb.set(i, 0, 1.0, 1.0, 0.9)
	# 	@rgb.trigger(i)
	# end
	# using their selection...
	m = input.gets
	m.each do |d|
		data = d[:data]
		if [153].include?(data.first)
			i = data[1]
			d = data[2].to_f / 142
			puts "#{i} @ #{d}"
			@rgb.trigger(i, d)
		end

	end

end

# start = 0
# start_time = Time.now.to_f
# count = 0
# while(true)
# 	data = []
# 	(0..LEDS).each do |i|
# 		r = 0
# 		g = 0
# 		b = 0;

# 		v = start + (i * 5);

# 		while (v >= 1536)
# 			v -= 1536
# 		end

# 		if (v < 256)
# 			r = 255
# 			g = v
# 		elsif v < 512 
# 			g = 255
# 			r = 255 - v
# 		elsif v < 768
# 			g = 255
# 			b = v - 512
# 		elsif v < 1024
# 			b = 255
# 			g = 1023 - v
# 		elsif v < 1280
# 			b = 255
# 			r = v - 768
# 		elsif v < 1536
# 			r = 255
# 			b = 1535 - v
# 		end

# 		data << [r, g, b]
# 	end
# 	data = [LEDS] + data.flatten
# 	set_multi(data)

# 	start += 5
# 	start = 0 if start >= 1536

	# count += 1
	# duration = (Time.now.to_f - start_time).to_f
	# puts "Count: #{count} over #{duration} is #{count.to_f / duration.to_f}"

# end

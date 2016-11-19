require_relative 'serial_command'
require 'pp'

class Rgb
	
	READY = 255
	CLEAR = 253
	SET = 254

	def initialize(led_count)
		@led_count = led_count
		@color_data = @led_count.times.map {[0, 0, 0]}.flatten
		@decays = @led_count.times.map {[0, 0, 0]}.flatten
		@triggers = {}
		@serial = SerialCommand.new '/dev/tty.usbserial-A600H19G', 115200
		@serial.connect!
	end

	def start
		puts "Rgb::start"
		wait_until_ready
		puts "Rgb::start - starting thread"
		@thread = Thread.new { update_loop }
	end

	def set(led, r, g, b, decay = 1)
		index = led * 3
		@color_data[index + 0] = (r * 255.0).to_i
		@color_data[index + 1] = (g * 255.0).to_i
		@color_data[index + 2] = (b * 255.0).to_i
		@decays[index + 0] = decay.to_f
		@decays[index + 1] = decay.to_f
		@decays[index + 2] = decay.to_f
	end

	def add(led, r, g, b, decay = 1)
		index = led * 3
		@color_data[index + 0] = @color_data[index + 0].to_i + (r * 255.0).to_i
		@color_data[index + 1] = @color_data[index + 1].to_i + (g * 255.0).to_i
		@color_data[index + 2] = @color_data[index + 2].to_i + (b * 255.0).to_i
		 @decays[index + 0] = clamp(@decays[index + 0].to_f + decay.to_f, 0, 0.9)
		 @decays[index + 1] = clamp(@decays[index + 1].to_f + decay.to_f, 0, 0.9)
		 @decays[index + 2] = clamp(@decays[index + 2].to_f + decay.to_f, 0, 0.9)
	end

	def add_trigger(id, leds, r, g, b, decay)
		@triggers[id] ||= []
		@triggers[id] << [leds, r, g, b, decay]
	end

	def trigger(id, force = 1)
		triggers = @triggers[id]
		if triggers
			triggers.each do |trigger|
				trigger[0].each do |i|
					add(i,
						force * trigger[1],
						force * trigger[2],
						force * trigger[3],
						force * trigger[4])
				end
			end
		end
	end

	private
	def wait_until_ready
		puts "Rgb::wait_until_ready"
		while @serial.wait_for(CLEAR, 100)
			puts "Wait..."
			sleep 0.5
			@serial.write(CLEAR)
		end
	end

	def apply_decay
		@led_count.times do |i|
			s = i * 3
			(s..(s+2)).each do |j|
				@color_data[j] = (clamp(@color_data[j], 0, 255) * clamp(@decays[j], 0.0, 1.0)).to_i
			end
		end
	end

	def clamp(value, min, max)
		if value < min
			return min
		elsif value > max
			return max
		else
			return value
		end
	end

	def update_loop

		# start_time = Time.now.to_f
		# count = 0
		while(true)
			apply_decay
			set_multi([@led_count] + @color_data)
			# count += 1
			# duration = (Time.now.to_f - start_time).to_f
			# puts "Count: #{count} over #{duration} is #{count.to_f / duration.to_f}"
		end
	end

	def set_multi(data)
		@serial.write(SET, data)
		@serial.wait_for(SET)
	end	

end